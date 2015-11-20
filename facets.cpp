/**
 *	facets.cpp
 *	-----------------------------------------------------------------------
 *	See "facets.h" for a description.
 */

using namespace std;

#include "facets.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facets::Facets()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Facets &f)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Facets");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Facets_ptr &f)
{
	return strm << *f;
}

/**
 *	Factory method using default constructor.
 */
Facets_ptr Facets::create()
{
	return Facets_ptr(new Facets());
}