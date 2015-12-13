/**
 *	entities.cpp
 *	-----------------------------------------------------------------------
 *	See "entities.h" for a description.
 */

using namespace std;

#include "entities.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Entities::Entities()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entities &f)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Entities");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Entities_ptr &f)
{
	return strm << *f;
}

/**
 *	Factory method using default constructor.
 */
Entities_ptr Entities::create()
{
	return Entities_ptr(new Entities());
}