/**
 *	skeleton.cpp
 *	-----------------------------------------------------------------------
 *	See "skeleton.h" for a description.
 */

using namespace std;

#include "skeleton.h"
#include <iostream>
#include "exceptions.h"

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

PlanBuilderSnapshot_ptr Skeleton::_buildPlan()
{
	//TODO: implement method
	_plan = Plan::create(_app, _spec, _side);
	return PlanBuilderSnapshot::create();
}

PathBuilderSnapshot_ptr Skeleton::_buildLower()
{
	//TODO: implement method
	_lower = Path::create(_app, _spec, _plan);
	return PathBuilderSnapshot::create();
}

PathBuilderSnapshot_ptr Skeleton::_buildUpper()
{
	//::TODO: implement method
	_upper = Path::create(_lower);
	return PathBuilderSnapshot::create();
}

Skeleton_ptr Skeleton::create(Application_ptr &app, Specification &spec, Side side)
{
	return Skeleton_ptr(new Skeleton(app, spec, side));
}

int Skeleton::getIterations()
{
	return _iter;
}

Application_ptr Skeleton::getApplication()
{
	return _app;
}

Specification Skeleton::getSpecification()
{
	return _spec;
}

Side Skeleton::getSide()
{
	return _side;
}

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