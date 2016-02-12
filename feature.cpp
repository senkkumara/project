using namespace std;

#include "feature.h"

Feature2D_ptr Feature2D::create(SurfaceRegion2D_ptr &r)
{
	return Feature2D_ptr(new Feature2D(r));
}

Feature2D_ptr Feature2D::create(SurfaceRegion2D_ptr &r, 
									   SurfaceTransition2D_ptr &out)
{
	return Feature2D_ptr(new Feature2D(r, out));
}

SurfaceRegion2D_ptr Feature2D::getRegion()
{
	return _region;
}

SurfaceTransition2D_ptr* Feature2D::getTransitions()
{
	return _trans;
}

SurfaceTransition2D_ptr Feature2D::in()
{
	return _trans[0];
}

SurfaceTransition2D_ptr Feature2D::out()
{
	return _trans[1];
}

SurfaceRegion2D::Type Feature2D::getType()
{
	return _region->getType();
}

void Feature2D::setIn(SurfaceTransition2D_ptr &t)
{
	_trans[0] = t;
}

void Feature2D::setOut(SurfaceTransition2D_ptr &t)
{
	_trans[1] = t;
}

Feature2D::Feature2D(SurfaceRegion2D_ptr &r)
{
	//TODO: implement method
}

Feature2D::Feature2D(SurfaceRegion2D_ptr &r, SurfaceTransition2D_ptr &out)
{
	//TODO: implement method
}