/**
 *	feature3Ds.cpp
 *	-----------------------------------------------------------------------
 *	See "feature3Ds.h" for a description.
 */

using namespace std;

#include "feature3ds.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature3Ds::Feature3Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature3Ds &f)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Feature3D");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature3Ds_ptr &f)
{
	return strm << *f;
}

/**
 *	Factory method using default constructor.
 */
Feature3Ds_ptr Feature3Ds::create()
{
	return Feature3Ds_ptr(new Feature3Ds());
}