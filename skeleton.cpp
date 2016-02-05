/**
 *	skeleton.cpp
 *	-----------------------------------------------------------------------
 *	See "skeleton.h" for a description.
 */

using namespace std;

#include "skeleton.h"
#include <iostream>
#include "exceptions.h"

/**
 *	(Private) Constructor requiring an application, specification and side
 *	arguments.
 */
Skeleton::Skeleton(Application_ptr &app, Specification &spec, Side side)
{
	//TODO: implement method - including snapshot functionality
	_app = app;
	_spec = spec;
	_side = side;
	_iter = 0;

	SkeletonBuilderSnapshot_ptr sn =
		SkeletonBuilderSnapshot::create();

	do
	{
		_iter++;
		if (! _buildPlan()) continue;
		if (! _buildLower()) continue;
		if (! _buildUpper()) continue;
	}
	while (! sn->isValid() && _iter < 10);
}

/**
 *	(Private) Build the plan for the rail.
 */
PlanBuilderSnapshot_ptr Skeleton::_buildPlan()
{
	//TODO: implement method
	_plan = Plan::create(_app, _spec, _side);
	return PlanBuilderSnapshot::create();
}

/**
 *	(Private) Builds the lower rail.
 */
PathBuilderSnapshot_ptr Skeleton::_buildLower()
{
	//TODO: implement method
	_lower = Path::create(_app, _spec, _plan);
	return PathBuilderSnapshot::create();
}

/**
 *	(Private) Builds the upper rail - by offsetting the lower rail.
 */
PathBuilderSnapshot_ptr Skeleton::_buildUpper()
{
	//::TODO: implement method
	_upper = Path::create(_lower);
	return PathBuilderSnapshot::create();
}

/**
 *	Factory method for the constuctor using an application, specification
 *	and side arguments.
 */
Skeleton_ptr Skeleton::create(Application_ptr &app, Specification &spec,
							  Side side)
{
	return Skeleton_ptr(new Skeleton(app, spec, side));
}

/**
 *	Get the current iteration of the skeleton build.
 */
int Skeleton::getIteration()
{
	return _iter;
}

/**
 *	Get the application the skeleton is built on.
 */
Application_ptr Skeleton::getApplication()
{
	return _app;
}

/**
 *	Get the specification the skeleton is built using.
 */
Specification Skeleton::getSpecification()
{
	return _spec;
}

/**
 *	Get the side the skeleton is built on.
 */
Side Skeleton::getSide()
{
	return _side;
}

/**
 *	Get the plan belonging to the skeleton.
 */
Plan_ptr Skeleton::getPlan()
{
	return _plan;
}

/**
 *	Get the lower rail path for the skeleton.
 */
Path_ptr Skeleton::getLower()
{
	return _lower;
}

/**
 *	Get the upper rail path for the skeleton.
 */
Path_ptr Skeleton::getUpper()
{
	return _upper;
}

/**
 *	(Private) Default constructor.
 */
SkeletonBuilderSnapshot::SkeletonBuilderSnapshot()
{
	//TODO: implement method
}

/**
 *	Factory method using the default constructor.
 */
SkeletonBuilderSnapshot_ptr SkeletonBuilderSnapshot::create()
{
	return SkeletonBuilderSnapshot_ptr(new SkeletonBuilderSnapshot());
}

/**
 *	Return boolean depending on whether the solution snapshot is valid.
 */
bool SkeletonBuilderSnapshot::isValid()
{
	//TODO: implement method
	return true;
}