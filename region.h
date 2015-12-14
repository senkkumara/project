#ifndef REGION_H
#define REGION_H

/**
 *	region.h
 *	---------------------------------------------------------------------------
 *	A Region is a 2D (surface) or 3D (volume) space used in the calculation of
 *	collision detection when creating the rail.
 */

using namespace std;

#include <memory>
#include <vector>
#include "edge.h"
#include "entity.h"

class SurfaceRegion;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceRegion> SurfaceRegion_ptr;

class VolumeRegion;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeRegion> VolumeRegion_ptr;

/**
 *	A 2D planar surface used for collision detection.
 */
class SurfaceRegion
{
private:
	// Constructors
	SurfaceRegion();

	// Fields (private)
	vector<Entity_ptr>	_edges;

public:
	// Factories
	static SurfaceRegion_ptr create();

	// Methods (public)
	bool intercept(Edge_ptr &e);
};

/**
 *	A 3D volume used for collision detection.
 */
class VolumeRegion
{
private:
	// Constructors
	VolumeRegion();

	// Fields (private)
	SurfaceRegion_ptr		_base;
	SurfaceRegion_ptr		_ceiling;
	vector<SurfaceRegion>	_sides;

public:
	// Factories
	static VolumeRegion_ptr create();
};

#endif