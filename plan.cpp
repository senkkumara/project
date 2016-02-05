using namespace std;

#include "plan.h"
#include "utils.h"

/**
 *	(Private) Constructs a Plan from an Application and Specification
 *	arguments.
 */
Plan::Plan(Application_ptr &app, Specification &spec, Side side)
{
	_app = app;
	_spec = spec;
	_side = side;

	_build();
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
	Feature2Ds_ptr fs = Feature2Ds::create();

	// Build the lines...
	_buildLines();

	// Only build radii if more than one line
	if (fs->size() < 2)
	{
		// Build the radii...
		_buildRads();
		_checkRads();

		// Optimise the path... (if it has radii, otherwise its just a
		// straight rail and is intrinsically optimised!)
		_optimise();
	}

}

/**
 *	(Private) Build the lines using edges and fit.
 */
void Plan::_buildLines()
{
	// Build the first line from the first edge
	if (_active->size() < 1)
	{
		return;		//TODO: add exception handling
	}

	Edge_ptr e = _active->first();
	Feature2DLine_ptr line = Feature2DLine::create(e, _passive, side);
	_lines->add(line);

	for (int i = 1; i < _active->size(); i++)
	{
		e = _active->get(i);

		// Attempt to add edge to current line
		if (! b->append(e))
		{
			// Create new line
			b = Feature2DLine::create(e, pass, fit);
			fs->add((Feature2D_ptr)b);
		}
	}
}

/**
 *	(Private) Build radii between the lines.
 */
void Plan::_buildRads()
{
	Feature2DLine_ptr l[2];
	Feature2DRad_ptr r;

	// Add rads between each pair of lines
	for (int i = 0; i < fs->size() - 1; i++)
	{
		l[0] = Feature2DLine::cast(fs->get(i));
		l[1] = Feature2DLine::cast(fs->get(i + 1));
		r = Feature2DRad::create(l[0], l[1], pass);
		fs->insert((Feature2D_ptr)r, i + 1);
	}
}

/**
 *	(Private) Ensure that the created radii are physically possible and do
 *	not break the design rules.
 */
void Plan::_checkRads()
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
 *	
 */
void Plan::_calculateQuality()
{
	//TODO: implement method
}

void Plan::_fixFeature(Feature2D_ptr &f)
{
	//TODO: implement method
}

/**
 *	Factory method using the constructor with an Application and 
 *	Specification argument.
 */
Plan_ptr Plan::create(Application_ptr &app, Specification &spec, Side side)
{
	return Plan_ptr(new Plan(app, spec, side));
}

/**
 *	(Private) Constructs a Plan Builder Snapshot.
 */
PlanBuilderSnapshot::PlanBuilderSnapshot()
{
	//TODO: implement method
}

/**
 *	Factory method using the constructor with no arguments.
 */
PlanBuilderSnapshot_ptr PlanBuilderSnapshot::create()
{
	return PlanBuilderSnapshot_ptr(new PlanBuilderSnapshot());
}