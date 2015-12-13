using namespace std;

#include "skeleton.h"
#include <iostream>
#include "exceptions.h"

Skeleton::Skeleton(Application_ptr &app, Specification &spec)
{
	_app = app;
	_spec = spec;
	_init();

	SkeletonBuilderSnapshot_ptr snapshot =
		SkeletonBuilderSnapshot::create();

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

PlanBuilderSnapshot_ptr Skeleton::_buildPlan()
{
	_plan = Plan::create(_app, _spec);
	return PlanBuilderSnapshot::create();
}

PathBuilderSnapshot_ptr Skeleton::_buildLower()
{
	_lower = Path::create(_app, _spec, _plan);
	return PathBuilderSnapshot::create();
}

PathBuilderSnapshot_ptr Skeleton::_buildUpper()
{
	_upper = Path::create(_lower);
	return PathBuilderSnapshot::create();
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

SkeletonBuilderSnapshot::SkeletonBuilderSnapshot()
{

}

SkeletonBuilderSnapshot_ptr SkeletonBuilderSnapshot::create()
{
	return SkeletonBuilderSnapshot_ptr(new SkeletonBuilderSnapshot());
}

bool SkeletonBuilderSnapshot::isValid()
{
	return true;
}