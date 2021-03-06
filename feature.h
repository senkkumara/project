#ifndef FEATURE_H
#define FEATURE_H

using namespace std;

#include <memory>
#include <vector>
#include "entities.h"
#include "entity.h"
#include "edges.h"
#include "edge.h"
#include "region.h"
#include "utils.h"

class Feature2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature2D> Feature2D_ptr;

class Feature3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Feature3D> Feature3D_ptr;

/**
 *	2D feature.
 */
class Feature2D
{
public:
	// Factories
	static Feature2D_ptr		create(SurfaceRegion2D_ptr &r);
	static Feature2D_ptr		create(SurfaceRegion2D_ptr &r,
		SurfaceTransition2D_ptr &out);
	static Feature2D_ptr		create(SurfaceRegion2D_ptr &r,
		SurfaceTransition2D_ptr &out, SurfaceTransition2D_ptr &in);

	// Methods (public)
	SurfaceRegion2D_ptr			getRegion();
	SurfaceTransition2D_ptr*	getTransitions();
	SurfaceTransition2D_ptr		in();
	SurfaceTransition2D_ptr		out();
	SurfaceRegion2D::Type		getType();
	void						setIn(SurfaceTransition2D_ptr &t);
	void						setOut(SurfaceTransition2D_ptr &t);

private:
	// Constructors
	Feature2D(SurfaceRegion2D_ptr &r);
	Feature2D(SurfaceRegion2D_ptr &r, SurfaceTransition2D_ptr &out);
	Feature2D(SurfaceRegion2D_ptr &r, SurfaceTransition2D_ptr &out,
		SurfaceTransition2D_ptr &in);

	// Fields (private)
	SurfaceRegion2D_ptr			_region;
	SurfaceTransition2D_ptr		_trans[2];

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature2D &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature2D_ptr &f);
};

/**
 *	Generic 3D feature
 */
class Feature3D
{
public:
	// Factories
	static Feature3D_ptr		create(SurfaceRegion3D_ptr &r);
	static Feature3D_ptr		create(SurfaceRegion3D_ptr &r,
		SurfaceTransition3D_ptr &out);
	static Feature3D_ptr		create(SurfaceRegion3D_ptr &r,
		SurfaceTransition3D_ptr &out, SurfaceTransition3D_ptr &in);

	// Methods (public)
	SurfaceRegion3D_ptr			getRegion();
	SurfaceTransition3D_ptr*	getTransitions();
	SurfaceTransition3D_ptr		in();
	SurfaceTransition3D_ptr		out();
	SurfaceRegion3D::Type		getType();
	void						setIn(SurfaceTransition3D_ptr &t);
	void						setOut(SurfaceTransition3D_ptr &t);

private:
	// Constructors
	Feature3D(SurfaceRegion3D_ptr &r);
	Feature3D(SurfaceRegion3D_ptr &r, SurfaceTransition3D_ptr &out);
	Feature3D(SurfaceRegion3D_ptr &r, SurfaceTransition3D_ptr &out,
		SurfaceTransition3D_ptr &in);

	// Fields (private)
	SurfaceRegion3D_ptr			_region;
	SurfaceTransition3D_ptr		_trans[2];

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature3D &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Feature3D_ptr &f);
};

#endif