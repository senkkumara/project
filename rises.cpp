/**
 *	rises.cpp
 *	-----------------------------------------------------------------------
 *	See "rises.h" for a description.
 */

using namespace std;

#include "rises.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Rises::Rises()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Rises &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Rises");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Rises_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
Rises_ptr Rises::create()
{
	return Rises_ptr(new Rises());
}