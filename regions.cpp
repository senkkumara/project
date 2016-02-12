/**
 *	regions.cpp
 *	-----------------------------------------------------------------------
 *	See "regions.h" for a description.
 */

using namespace std;

#include "regions.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
SurfaceRegion2Ds::SurfaceRegion2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceRegion2Ds &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< SurfaceRegion2Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceRegion2Ds_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
SurfaceRegion2Ds_ptr SurfaceRegion2Ds::create()
{
	return SurfaceRegion2Ds_ptr(new SurfaceRegion2Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
SurfaceTransition2Ds::SurfaceTransition2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceTransition2Ds &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< SurfaceTransition2Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceTransition2Ds_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
SurfaceTransition2Ds_ptr SurfaceTransition2Ds::create()
{
	return SurfaceTransition2Ds_ptr(new SurfaceTransition2Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
SurfaceRegion3Ds::SurfaceRegion3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceRegion3Ds &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< SurfaceRegion3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceRegion3Ds_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
SurfaceRegion3Ds_ptr SurfaceRegion3Ds::create()
{
	return SurfaceRegion3Ds_ptr(new SurfaceRegion3Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
SurfaceTransition3Ds::SurfaceTransition3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceTransition3Ds &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< SurfaceTransition3Ds");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const SurfaceTransition3Ds_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
SurfaceTransition3Ds_ptr SurfaceTransition3Ds::create()
{
	return SurfaceTransition3Ds_ptr(new SurfaceTransition3Ds());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
VolumeRegions::VolumeRegions()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const VolumeRegions &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< VolumeRegions");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const VolumeRegions_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
VolumeRegions_ptr VolumeRegions::create()
{
	return VolumeRegions_ptr(new VolumeRegions());
}

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
VolumeTransitions::VolumeTransitions()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const VolumeTransitions &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< VolumeTransitions");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const VolumeTransitions_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
VolumeTransitions_ptr VolumeTransitions::create()
{
	return VolumeTransitions_ptr(new VolumeTransitions());
}