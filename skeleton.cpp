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
 *	Get the paths belonging to the skeleton.
 */
Path_ptr* Skeleton::getPaths()
{
	return _path;
}

/**
 *	Get the lower rail path for the skeleton.
 */
Path_ptr Skeleton::getLower()
{
	return _path[0];
}

/**
 *	Get the upper rail path for the skeleton.
 */
Path_ptr Skeleton::getUpper()
{
	return _path[1];
}

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

	_plan = Plan::create(_app, _spec, _side);
	_path[0] = Path::create(_app, _spec, _plan);
	_path[1] = Path::create(_app, _spec, _plan);
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

/**
 *	(Private) Default constructor.
 */
SkeletonBuilderSnapshot::SkeletonBuilderSnapshot()
{
	//TODO: implement method
}