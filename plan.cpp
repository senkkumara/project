using namespace std;

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
 *	Apply a previously created Plan Builder Snapshot.
 */
bool Plan::applyChanges(PlanBuilderSnapshot_ptr &s)
{
	//TODO: implement method
	return true;
}

/**
 *	Remove a previously applied Plan Builder Snapshot.
 */
bool Plan::removeChanges(PlanBuilderSnapshot_ptr &s)
{
	//TODO: implement method
	return true;
}

/**
 *	(Private) Constructs a Plan from an Application and Specification
 *	arguments.
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

	switch (_side)
	{
	case SIDE_LEFT:
		_active = _app->left();
		_passive = _app->right();
		break;

	case SIDE_RIGHT:
		_active = _app->right();
		_passive = _app->left();
		break;

	default:
		//TODO: throw exception
		break;
	};

	_regions = SurfaceRegion2Ds::create();
	_trans = SurfaceTransition2Ds::create();
	_feats = Feature2Ds::create();

	_quality = 0.0;
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
	if (_feats->size() < 2)
	{
		// Build the radii...
		_buildTransitions();
		_checkTransitions();

		// Optimise the plan... (if it has radii, otherwise its just a
		// straight rail and is intrinsically optimised!)
		_optimise();
	}
}

/**
 *	(Private) Build the regions using edges and fit.
 */
void Plan::_buildRegions()
{
	// Only build if there is 
	if (_active->size() < 1)
	{
		return;		//TODO: add exception handling
	}

	Entity2D::Fit2D fit = _mapFit();

	// Build the first region from the first edge
	Edge_ptr e = _active->first();
	SurfaceRegion2D_ptr reg = SurfaceRegion2D::create(e, _passive, fit);
	_regions->add(reg);

	Feature2D_ptr feat = Feature2D::create(reg);
	_feats->add(feat);

	for (int i = 1; i < _active->size(); i++)
	{
		e = _active->get(i);

		// Attempt to add edge to current region
		if (! reg->append(e))
		{
			// Create new region
			reg = SurfaceRegion2D::create(e, _passive, fit);
			_regions->add(reg);

			feat = Feature2D::create(reg);
			_feats->add(feat);
		}
	}
}

/**
 *	(Private) Build transitions between the regions.
 */
void Plan::_buildTransitions()
{
	Feature2D_ptr f[2];
	SurfaceRegion2D_ptr r[2];
	SurfaceTransition2D_ptr t;

	// Add transition between each pair of regions
	for (int i = 0; i < _feats->size() - 2; i++)
	{
		f[0] = _feats->get(i);
		f[1] = _feats->get(i + 1);
		r[0] = f[0]->getRegion();
		r[1] = f[1]->getRegion();

		t = SurfaceTransition2D::create(r[0], r[1], _passive);
		_trans->add(t);

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
}

/**
 *	(Private) Iterate to improve the quality of the path.
 */
void Plan::_optimise()
{
	//TODO: implement method
}

/**
 *	(Private) Recalculate the quality of the Plan.
 */
void Plan::_calculateQuality()
{
	//TODO: implement method
}

/**
 *	(Private) Fix a Feature so it is no longer breaking the design rules /
 *	geometry can be created.
 */
void Plan::_fixFeature(Feature2D_ptr &f)
{
	//TODO: implement method
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

/**
 *	Factory method using the constructor with no arguments.
 */
PlanBuilderSnapshot_ptr PlanBuilderSnapshot::create()
{
	return PlanBuilderSnapshot_ptr(new PlanBuilderSnapshot());
}

/**
 *	(Private) Constructs a Plan Builder Snapshot.
 */
PlanBuilderSnapshot::PlanBuilderSnapshot()
{
	//TODO: implement method
}