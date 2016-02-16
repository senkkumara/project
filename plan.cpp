/**
 *	plan.cpp
 *	---------------------------------------------------------------------------
 *	See "plan.h" for a description.
 */

using namespace std;

#include "exceptions.h"
#include <iostream>
#include "plan.h"
#include "utils.h"

/**
 *	Factory method using the constructor with an Application and 
 *	Specification argument.
 */
Plan_ptr Plan::create(Application_ptr &app, Specification &spec)
{
	return Plan_ptr(new Plan(app, spec));
}

/**
 *	Factory method using the constructor with an Application and 
 *	Specification and side arguments.
 */
Plan_ptr Plan::create(Application_ptr &app, Specification &spec, Side side)
{
	return Plan_ptr(new Plan(app, spec, side));
}

/**
 *	Get the application the plan is based on.
 */
Application_ptr Plan::getApplication()
{
	return _app;
}

/**
 *	Get the specification the plan is based on.
 */
Specification Plan::getSpecification()
{
	return _spec;
}

/**
 *	Get the side the plan is for.
 */
Side Plan::getSide()
{
	return _side;
}

/**
 *	Get the iteration of the plan.
 */
int Plan::getIteration()
{
	return _iter;
}

/**
 *	Get the quality of the plan.
 */
double Plan::getQuality()
{
	return _quality;
}

/**
 *	Get the boundary of the plan. The zero-th element is the
 *	rail-side and the one-th is the offset side.
 */
Edges_ptr* Plan::getBoundary()
{
	return _boundary;
}

/**
 *	Get the active boundary of the plan - the one on
 *	the same side of the rail.
 */
Edges_ptr Plan::getActive()
{
	return _boundary[0];
}

/**
 *	Get the passive boundary of the plan - the one on the other
 *	side of the stiarcase from the rail.
 */
Edges_ptr Plan::getPassive()
{
	return _boundary[1];
}

/**
 *	Get the regions the plan consists of.
 */
SurfaceRegion2Ds_ptr Plan::getRegions()
{
	return _regions;
}

/**
 *	Get the transitions the plan consists of.
 */
SurfaceTransition2Ds_ptr Plan::getTransitions()
{
	return _trans;
}

/**
 *	Get the features the plan consists of.
 */
Feature2Ds_ptr Plan::getFeatures()
{
	return _feats;
}

/**
 *	Apply a previously created PlanBuilder Snapshot.
 */
bool Plan::applyChanges(PlanBuilderSnapshot_ptr &s)
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::applyChanges");
	return true;
}

/**
 *	Remove a previously applied PlanBuilder Snapshot.
 */
bool Plan::removeChanges(PlanBuilderSnapshot_ptr &s)
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::removeChanges");
	return true;
}

/**
 *	(Private) Constructs a Plan from an Application and Specification
 *	arguments.
 *
 *	Note, since no side was specified, it takes it from the Specification.
 *	The assumption is that only one side was specified and therefore this
 *	plan forms part of the one and only solution.
 */
Plan::Plan(Application_ptr &app, Specification &spec)
{
	_init(app, spec, spec.Side);
	_build();
}

/**
 *	(Private) Constructs a Plan from an Application, Specification and Side
 *	arguments.
 */
Plan::Plan(Application_ptr &app, Specification &spec, Side side)
{
	_init(app, spec, side);
	_build();
}

/**
 *	(Private) Initialise member fields.
 */
void Plan::_init(Application_ptr &app, Specification &spec, Side side)
{
	_app = app;
	_spec = spec;
	_side = side;
	_iter = 0;
	_quality = 0.0;

	switch (_side)
	{
	case SIDE_LEFT:
		_boundary[0] = _app->left();
		_boundary[1] = _app->right();
		break;

	case SIDE_RIGHT:
		_boundary[0] = _app->right();
		_boundary[1] = _app->left();
		break;

	default:
		//TODO: throw exception
		break;
	};

	_regions = SurfaceRegion2Ds::create();
	_trans = SurfaceTransition2Ds::create();
	_feats = Feature2Ds::create();
}

/**
 *	(Private) Build a single potential plan - based on the active and passive
 *	edges and a provided side.
 *	
 *	The "Active" edge is the side that the rail will be placed and is therefore
 *	the one which is followed. The "Passive" edge is the other wall and is
 *	merely checked against for clashes.
 */
void Plan::_build()
{
	// Build the lines...
	_buildRegions();

	// Only build radii if more than one line
	/*
	if (_feats->size() < 2)
	{
		// Build the radii...
		_buildTransitions();
		_checkTransitions();

		// Optimise the plan... (if it has radii, otherwise its just a
		// straight rail and is intrinsically optimised!)
		_optimise();
	}*/
}

/**
 *	(Private) Build the regions using edges and fit.
 */
void Plan::_buildRegions()
{
	// Only build if there is 
	if (_boundary[0]->size() < 1)
	{
		throw SolutionBuildException();
	}

	Entity2D::Fit2D fit = _mapFit();

	// Build the first region from the first edge
	Edge_ptr e = _boundary[0]->first();
	SurfaceRegion2D_ptr reg = SurfaceRegion2D::create(e, _boundary[1], fit);
	_regions->add(reg);

	Feature2D_ptr feat = Feature2D::create(reg);
	_feats->add(feat);

	for (int i = 1; i < _boundary[0]->size(); i++)
	{
		e = _boundary[0]->get(i);

		// Attempt to add edge to current region
		if (! reg->append(e))
		{
			// Create new region
			reg = SurfaceRegion2D::create(e, _boundary[1], fit);
			_regions->add(reg);

			feat = Feature2D::create(reg);
			_feats->add(feat);
		}
	}

	cout << _regions->size() << endl;
	cout << _regions->get(0)->inner()->size() << endl;
	cout << _regions->get(0)->inner()->getXCoefficients()[0] << " " << _regions->get(0)->inner()->getXCoefficients()[1] << endl;
	cout << _regions->get(0)->inner()->getYCoefficients()[0] << " " << _regions->get(0)->inner()->getYCoefficients()[1] << endl;
}

/**
 *	(Private) Build transitions between the regions.
 */
void Plan::_buildTransitions()
{
	Feature2D_ptr f[2];			// holder for WIP features
	SurfaceRegion2D_ptr r[2];	// holder for WIP regions
	SurfaceTransition2D_ptr t;	// transition being built

	// Add transition between each pair of regions
	for (int i = 0; i < _feats->size() - 2; i++)
	{
		f[0] = _feats->get(i);
		f[1] = _feats->get(i + 1);
		r[0] = f[0]->getRegion();
		r[1] = f[1]->getRegion();

		t = SurfaceTransition2D::create(r[0], r[1], _boundary[1]);
		_trans->add(t);

		// Set transition on the features
		f[0]->setOut(t);
		f[1]->setIn(t);
	}
}

/**
 *	(Private) Ensure that the created radii are physically possible and do
 *	not break the design rules.
 */
void Plan::_checkTransitions()
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::_checkTransitions");
}

/**
 *	(Private) Iterate to improve the quality of the path.
 */
void Plan::_optimise()
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::_optimise");
}

/**
 *	(Private) Recalculate the quality of the Plan.
 */
void Plan::_calculateQuality()
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::_calculateQuality");
}

/**
 *	(Private) Fix a Feature so it is no longer breaking the design rules /
 *	geometry can be created.
 */
void Plan::_fixFeature(Feature2D_ptr &f)
{
	//TODO: implement method
	throw MethodNotImplementedException("Plan::_fixFeature");
}

/**
 *	(Private) Map the side the plan is to be placed on to the fit used when
 *	creating the entities.
 */
Entity2D::Fit2D Plan::_mapFit()
{
	switch (_side)
	{
	case SIDE_LEFT:
		return Entity2D::FIT2D_LEFT;

	case SIDE_RIGHT:
		return Entity2D::FIT2D_RIGHT;

	default:
		return Entity2D::FIT2D_BEST;
	}
}