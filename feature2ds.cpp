/**
 *	feature2Ds.cpp
 *	-----------------------------------------------------------------------
 *	See "feature2Ds.h" for a description.
 */

using namespace std;

#include "feature2ds.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature2Ds::Feature2Ds()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature2Ds &f)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Feature2D");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature2Ds_ptr &f)
{
	return strm << *f;
}

/**
 *	Factory method using default constructor.
 */
Feature2Ds_ptr Feature2Ds::create()
{
	return Feature2Ds_ptr(new Feature2Ds());
}