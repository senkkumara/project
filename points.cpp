/**
 *	points.cpp
 *	-----------------------------------------------------------------------
 *	See "points.h" for a description.
 */

using namespace std;

#include "points.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Points::Points()
{
	// do nothing...
}

/**
 *	(Private) Mirror the points about the axis specified by an index
 *	(X = 0, Y = 1, Z = 2).
 */
void Points::_mirrorComponent(int index)
{
	for (int i = 0; i < size(); i++)
	{
		this->get(i)->_setComponent(index,
			this->get(i)->_getComponent(index) * -1);
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Points &p)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Points");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Points_ptr &p)
{
	return strm << *p;
}

/**
 *	Factory method using default constructor.
 */
Points_ptr Points::create()
{
	return Points_ptr(new Points());
}

/**
 *	Mirror the points about the X-axis.
 */
void Points::mirrorX()
{
	_mirrorComponent(0);
}

/**
 *	Mirror the points about the Y-axis.
 */
void Points::mirrorY()
{
	_mirrorComponent(1);
}

/**
 *	Mirror the points about the Z-axis.
 */
void Points::mirrorZ()
{
	_mirrorComponent(2);
}