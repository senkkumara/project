/**
 *	edges.cpp
 *	-----------------------------------------------------------------------
 *	See "edges.h" for a description.
 */

using namespace std;

#include "edges.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Edges::Edges()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edges &es)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Edges");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edges_ptr &es)
{
	return strm << *es;
}

/**
 *	Factory method using default constructor.
 */
Edges_ptr Edges::create()
{
	return Edges_ptr(new Edges());
}