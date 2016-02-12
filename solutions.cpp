/**
 *	solutions.cpp
 *	-----------------------------------------------------------------------
 *	See "solutions.h" for a description.
 */

using namespace std;

#include "enums.h"
#include "exceptions.h"
#include "solution.h"
#include "solutions.h"

/**
 *	Factory method using default constructor.
 */
Solutions_ptr Solutions::create()
{
	return Solutions_ptr(new Solutions());
}

/**
 *	Factory method using constructor with Specification and Application
 *	arguments.
 */
Solutions_ptr Solutions::create(Specification &spec, Application_ptr &app)
{
	return Solutions_ptr(new Solutions(spec, app));
}

/**
 *	(Private) Default constructor.
 */
Solutions::Solutions()
{
	// Do nothing...
}

/**
 *	(Private) Constructor requiring a Specification and Application
 *	arguments.
 *
 *	Do not use this directly, use the provided factory method.
 */
Solutions::Solutions(Specification &spec, Application_ptr &app)
{
	// Determine whether to build left, right or both
	if (spec.Side == SIDE_UNDEFINED)
	{
		add(Solution::create(spec, app, SIDE_LEFT));
		add(Solution::create(spec, app, SIDE_RIGHT));
	}
	else
	{
		add(Solution::create(spec, app, spec.Side));
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Solutions &s)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Solutions");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Solutions_ptr &s)
{
	return strm << *s;
}