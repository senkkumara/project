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

class SurfaceRegion2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceRegion2D> SurfaceRegion2D_ptr;

class SurfaceTransition2D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceTransition2D> SurfaceTransition2D_ptr;

class SurfaceRegion3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceRegion3D> SurfaceRegion3D_ptr;

class SurfaceTransition3D;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceTransition3D> SurfaceTransition3D_ptr;

class VolumeRegion;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeRegion> VolumeRegion_ptr;

class VolumeTransition;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeTransition> VolumeTransition_ptr;

/**
 *	2D feature.
 */
class SurfaceRegion2D
{
public:
	// Enumerations (public)
	typedef enum Type
	{
		SURFACEREGION2D_TYPE_STRAIGHT,
		SURFACEREGION2D_TYPE_SPECIAL
	};

	// Factories
	static SurfaceRegion2D_ptr create(Edge_ptr &e, Edges_ptr &b,
		Entity2D::Fit2D f);

	// Methods (public)
	bool				append(Edge_ptr &e);
	Edges_ptr*			getBoundary();
	Edges_ptr			getActive();
	Edges_ptr			getPassive();
	Entity2D::Fit2D		getFit();
	Type				getType();
	LineEntity2D_ptr	inner();
	LineEntity2D_ptr	outer();
	LineEntity2D_ptr	entry();
	LineEntity2D_ptr	exit();

private:
	// Constructors
	SurfaceRegion2D(Edge_ptr &e, Edges_ptr &b, Entity2D::Fit2D f);

	// Fields (private)
	Edges_ptr			_boundary[2];	// Full boundary
	Entity2D::Fit2D		_fit;			// How to fit lines to boundaries
	Type				_type;			// Type of surface (e.g. 'line')
	LineEntity2D_ptr	_inner;			// Rail side
	LineEntity2D_ptr	_outer;			// Clearnance arc
	LineEntity2D_ptr	_entry;			// Edge lift crosses to enter region
	LineEntity2D_ptr	_exit;			// Edge lift crosses to leave region
	
	// Methods (private)
	void	_init();
	bool	_intersects();
	bool	_intersects(Edges_ptr &e);
	bool	_intersects(Edge_ptr &e);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceRegion2D &f);

	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceRegion2D_ptr &f);
};

/**
 *	A 2D radius feature - a fillet between two straight lines.
 */
class SurfaceTransition2D
{
public:
	// Factories
	static SurfaceTransition2D_ptr create(SurfaceRegion2D_ptr &f1,
		SurfaceRegion2D_ptr &f2, Edges_ptr &e);

	// Methods (public)
	Edges_ptr*			getBoundary();
	Edges_ptr			getActive();
	Edges_ptr			getPassive();
	Entity2D::Fit2D		getFit();
	RadEntity2D_ptr		inner();
	LineEntity2D_ptr*	outer();
	LineEntity2D_ptr	entry();
	LineEntity2D_ptr	exit();

private:
	// Constructors
	SurfaceTransition2D(SurfaceRegion2D_ptr &f1, SurfaceRegion2D_ptr &f2,
		Edges_ptr &b);

	// Fields (private)
	Edges_ptr			_boundary[2];	// Full boundary
	Entity2D::Fit2D		_fit;			// How to fit lines to boundaries
	RadEntity2D_ptr		_inner;			// Rail side
	LineEntity2D_ptr	_outer[2];		// Clearnance arc
	LineEntity2D_ptr	_entry;			// Edge lift crosses to enter region
	LineEntity2D_ptr	_exit;			// Edge lift crosses to leave region

	// Methods (private)
	void _init();
	bool _intercept();
	bool _intercept(Edges_ptr &e);
	bool _intercept(Edge_ptr &e);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const SurfaceTransition2D &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceTransition2D_ptr &f);
};

/**
 *	2D feature.
 */
class SurfaceRegion3D
{
public:
	// Enumerations (public)
	typedef enum Type
	{
		SURFACEREGION3D_TYPE_STRAIGHT,
		SURFACEREGION3D_TYPE_CORNER,
		SURFACEREGION3D_TYPE_HELIX,
		SURFACEREGION3D_TYPE_SPLIT,
		SURFACEREGION3D_TYPE_SPECIAL
	};

	// Methods (public)
	Type getType();

private:
	// Fields (private)
	Type _type;
};

/**
 *	A 3D radius feature - a fillet between two straight lines.
 */
class SurfaceTransition3D
{

};

#endif