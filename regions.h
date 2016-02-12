#ifndef REGIONS_H
#define REGIONS_H

/**
 *	regions.h
 *	-----------------------------------------------------------------------
 *	A Regions object is container for one or more Region objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include "collection.h"
#include "region.h"

class SurfaceRegion2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceRegion2Ds> SurfaceRegion2Ds_ptr;

class SurfaceTransition2Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceTransition2Ds> SurfaceTransition2Ds_ptr;

class SurfaceRegion3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceRegion3Ds> SurfaceRegion3Ds_ptr;

class SurfaceTransition3Ds;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<SurfaceTransition3Ds> SurfaceTransition3Ds_ptr;

class VolumeRegions;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeRegions> VolumeRegions_ptr;

class VolumeTransitions;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<VolumeTransitions> VolumeTransitions_ptr;

/**
 *	Collection of SurfaceRegion2Ds.
 */
class SurfaceRegion2Ds : public Collection<SurfaceRegion2D_ptr, SurfaceRegion2Ds_ptr>
{
private:
	// Constructors
	SurfaceRegion2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const SurfaceRegion2Ds &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceRegion2Ds_ptr &r);

public:
	// Factories
	static SurfaceRegion2Ds_ptr create();
};

/**
 *	Collection of SurfaceTransition2Ds.
 */
class SurfaceTransition2Ds : public Collection<SurfaceTransition2D_ptr, SurfaceTransition2Ds_ptr>
{
private:
	// Constructors
	SurfaceTransition2Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const SurfaceTransition2Ds &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceTransition2Ds_ptr &r);

public:
	// Factories
	static SurfaceTransition2Ds_ptr create();
};

/**
 *	Collection of SurfaceRegion2Ds.
 */
class SurfaceRegion3Ds : public Collection<SurfaceRegion3D_ptr, SurfaceRegion3Ds_ptr>
{
private:
	// Constructors
	SurfaceRegion3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const SurfaceRegion3Ds &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceRegion3Ds_ptr &r);

public:
	// Factories
	static SurfaceRegion3Ds_ptr create();
};

/**
 *	Collection of SurfaceTransition3Ds.
 */
class SurfaceTransition3Ds : public Collection<SurfaceRegion3D_ptr, SurfaceTransition3Ds_ptr>
{
private:
	// Constructors
	SurfaceTransition3Ds();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const SurfaceTransition3Ds &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const SurfaceTransition3Ds_ptr &r);

public:
	// Factories
	static SurfaceTransition3Ds_ptr create();
};

/**
 *	Collection of VolumeRegions.
 */
class VolumeRegions : public Collection<VolumeRegion_ptr, VolumeRegions_ptr>
{
private:
	// Constructors
	VolumeRegions();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const VolumeRegions &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const VolumeRegions_ptr &r);

public:
	// Factories
	static VolumeRegions_ptr create();
};

/**
 *	Collection of VolumeTransitions.
 */
class VolumeTransitions : public Collection<VolumeRegion_ptr, VolumeTransitions_ptr>
{
private:
	// Constructors
	VolumeTransitions();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const VolumeTransitions &r);
	friend std::ostream &operator<<(std::ostream &strm,
		const VolumeTransitions_ptr &r);

public:
	// Factories
	static VolumeTransitions_ptr create();
};

#endif