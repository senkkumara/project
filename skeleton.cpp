using namespace std;

#include "skeleton.h"
#include <iostream>
#include "exceptions.h"

Skeleton::Skeleton(Application_ptr &app, Specification &spec)
{
	_app = app;
	_spec = spec;
	_init();

	Skeleton::SkeletonBuilderSnapshot_ptr snapshot =
		Skeleton::SkeletonBuilderSnapshot::create();

	do
	{
		_iter++;
		if (! _buildPlan()) continue;
		if (! _buildLower()) continue;
		if (! _buildUpper()) continue;
	}
	while (! snapshot->isValid() && _iter < 10);
}

void Skeleton::_init()
{
	_iter = 0;
}

Skeleton::PlanBuilderSnapshot_ptr Skeleton::_buildPlan()
{
	_plan = Plan::create(_app, _spec);
	return Skeleton::PlanBuilderSnapshot::create();
}

Skeleton::PathBuilderSnapshot_ptr Skeleton::_buildLower()
{
	_lower = Path::create(_app, _spec, _plan);
	return Skeleton::PathBuilderSnapshot::create();
}

Skeleton::PathBuilderSnapshot_ptr Skeleton::_buildUpper()
{
	_upper = Path::create(_lower);
	return Skeleton::PathBuilderSnapshot::create();
}

void Skeleton::_buildDatums()
{
	//TODO: implement method
}

Skeleton_ptr Skeleton::create(Application_ptr &app, Specification &spec)
{
	return Skeleton_ptr(new Skeleton(app, spec));
}

int Skeleton::getIterations()
{
	return _iter;
}

Application_ptr Skeleton::getApp()
{
	return _app;
}

Plan_ptr Skeleton::getPlan()
{
	return _plan;
}

Path_ptr Skeleton::lower()
{
	return _lower;
}

Path_ptr Skeleton::upper()
{
	return _upper;
}

Skeleton::SkeletonBuilderSnapshot::SkeletonBuilderSnapshot()
{

}

Skeleton::SkeletonBuilderSnapshot_ptr
	Skeleton::SkeletonBuilderSnapshot::create()
{
	return SkeletonBuilderSnapshot_ptr(new SkeletonBuilderSnapshot());
}

bool Skeleton::SkeletonBuilderSnapshot::isValid()
{
	return true;
}

Skeleton::PlanBuilderSnapshot::PlanBuilderSnapshot()
{

}

Skeleton::PlanBuilderSnapshot_ptr
	Skeleton::PlanBuilderSnapshot::create()
{
	return PlanBuilderSnapshot_ptr(new PlanBuilderSnapshot());
}

Skeleton::PathBuilderSnapshot::PathBuilderSnapshot()
{

}

Skeleton::PathBuilderSnapshot_ptr
	Skeleton::PathBuilderSnapshot::create()
{
	return PathBuilderSnapshot_ptr(new PathBuilderSnapshot());
}

PathType Skeleton::PathBuilderSnapshot::getType()
{
	return _type;
}