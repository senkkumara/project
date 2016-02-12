using namespace std;

#include "feature.h"

/**
 *
 */
Feature2D_ptr Feature2D::create(SurfaceRegion2D_ptr &r)
{
	return Feature2D_ptr(new Feature2D(r));
}

/**
 *
 */
Feature2D_ptr Feature2D::create(SurfaceRegion2D_ptr &r, 
								SurfaceTransition2D_ptr &out)
{
	return Feature2D_ptr(new Feature2D(r, out));
}

/**
 *
 */
Feature2D_ptr Feature2D::create(SurfaceRegion2D_ptr &r,
								SurfaceTransition2D_ptr &out,
								SurfaceTransition2D_ptr &in)
{
	return Feature2D_ptr(new Feature2D(r, out));
}

/**
 *
 */
SurfaceRegion2D_ptr Feature2D::getRegion()
{
	return _region;
}

/**
 *
 */
SurfaceTransition2D_ptr* Feature2D::getTransitions()
{
	return _trans;
}

/**
 *
 */
SurfaceTransition2D_ptr Feature2D::in()
{
	return _trans[0];
}

/**
 *
 */
SurfaceTransition2D_ptr Feature2D::out()
{
	return _trans[1];
}

/**
 *
 */
SurfaceRegion2D::Type Feature2D::getType()
{
	return _region->getType();
}

/**
 *
 */
void Feature2D::setIn(SurfaceTransition2D_ptr &t)
{
	_trans[0] = t;
}

/**
 *
 */
void Feature2D::setOut(SurfaceTransition2D_ptr &t)
{
	_trans[1] = t;
}

/**
 *
 */
Feature2D::Feature2D(SurfaceRegion2D_ptr &r)
{
	_region = r;
}

/**
 *
 */
Feature2D::Feature2D(SurfaceRegion2D_ptr &r, SurfaceTransition2D_ptr &out)
{
	_region = r;
	_trans[1] = out;
}

/**
 *
 */
Feature2D::Feature2D(SurfaceRegion2D_ptr &r, SurfaceTransition2D_ptr &out,
					 SurfaceTransition2D_ptr &in)
{
	_region = r;
	_trans[0] = in;
	_trans[1] = out;
}

/**
 *
 */
Feature3D_ptr Feature3D::create(SurfaceRegion3D_ptr &r)
{
	return Feature3D_ptr(new Feature3D(r));
}

/**
 *
 */
Feature3D_ptr Feature3D::create(SurfaceRegion3D_ptr &r, 
								SurfaceTransition3D_ptr &out)
{
	return Feature3D_ptr(new Feature3D(r, out));
}

/**
 *
 */
Feature3D_ptr Feature3D::create(SurfaceRegion3D_ptr &r,
								SurfaceTransition3D_ptr &out,
								SurfaceTransition3D_ptr &in)
{
	return Feature3D_ptr(new Feature3D(r, out));
}

/**
 *
 */
SurfaceRegion3D_ptr Feature3D::getRegion()
{
	return _region;
}

/**
 *
 */
SurfaceTransition3D_ptr* Feature3D::getTransitions()
{
	return _trans;
}

/**
 *
 */
SurfaceTransition3D_ptr Feature3D::in()
{
	return _trans[0];
}

/**
 *
 */
SurfaceTransition3D_ptr Feature3D::out()
{
	return _trans[1];
}

/**
 *
 */
SurfaceRegion3D::Type Feature3D::getType()
{
	return _region->getType();
}

/**
 *
 */
void Feature3D::setIn(SurfaceTransition3D_ptr &t)
{
	_trans[0] = t;
}

/**
 *
 */
void Feature3D::setOut(SurfaceTransition3D_ptr &t)
{
	_trans[1] = t;
}

/**
 *
 */
Feature3D::Feature3D(SurfaceRegion3D_ptr &r)
{
	_region = r;
}

/**
 *
 */
Feature3D::Feature3D(SurfaceRegion3D_ptr &r, SurfaceTransition3D_ptr &out)
{
	_region = r;
	_trans[1] = out;
}

/**
 *
 */
Feature3D::Feature3D(SurfaceRegion3D_ptr &r, SurfaceTransition3D_ptr &out,
					 SurfaceTransition3D_ptr &in)
{
	_region = r;
	_trans[0] = in;
	_trans[1] = out;
}