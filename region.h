#ifndef REGION_H
#define REGION_H

using namespace std;

#include <memory>
#include <vector>
#include "edge.h"
#include "entity.h"

class SurfaceRegion;
typedef shared_ptr<SurfaceRegion> SurfaceRegion_ptr;

class SurfaceRegion
{
private:
	vector<Entity_ptr>	_edges;

public:
	bool intercept(Edge_ptr &e);
};

class VolumeRegion;
typedef shared_ptr<VolumeRegion> VolumeRegion_ptr;

class VolumeRegion
{
private:
	SurfaceRegion_ptr		_base;
	SurfaceRegion_ptr		_ceiling;
	vector<SurfaceRegion>	_sides;

public:

};

#endif