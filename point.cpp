/**
 *	point.cpp
 *	-----------------------------------------------------------------------
 *	See "point.h" for a description.
 */

using namespace std;

#include "point.h"
#include <iostream>
#include <string>

/**
 *	(Private) Constructs a point based on three numeric
 *	arguments that represent the 3D position.
 *
 *	Do not use this directly, use the provided factory method.
 */
Point::Point(double xcoord = 0.0,
			 double ycoord = 0.0,
			 double zcoord = 0.0)
{
	std::vector<double> coords;
	coords.push_back(xcoord);
	coords.push_back(ycoord);
	coords.push_back(zcoord);
}

/**
 *	(Private) Constructs a point based on a vector containing
 *	the components of its position.
 *
 *	Do not use this directly, use the provided factory method.
 */
Point::Point(std::vector<double> &coords)
{
	_coords = coords;
}

/**
 *	(Private) Gets the component of the point position corresponding
 *	to the provided index (e.g. X has an index of 1).
 */
double Point::_getComponent(int index)
{
	return _coords.at(index);
}

/**
 *	(Private) Sets the component of the point position corresponding
 *	to the provided index (e.g. X has an index of 1).
 */
void Point::_setComponent(int index, double value)
{
	_coords.at(index) = value;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Point &p)
{
	return strm << '(' << p._coords.at(0) 
				<< ", " << p._coords.at(1)
				<< ", " << p._coords.at(2)
				<< ')' << endl;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Point_ptr &p)
{
	return strm << *p;
}

/**
 *	== operator overload.
 */
bool operator==(Point &cP1, Point &cP2)
{
	return (cP1.getX() == cP2.getX() &&
            cP1.getY() == cP2.getY() &&
            cP1.getZ() == cP2.getZ());
}

/**
 *	!= operator overload.
 */
bool operator!=(Point &cP1, Point &cP2)
{
	return !(cP1 == cP2);
}

/**
 *	Factory method using constructor with numeric arguments.
 */
Point_ptr Point::create(double xcoord = 0.0,
						double ycoord = 0.0,
						double zcoord = 0.0)
{
	return Point_ptr(new Point(xcoord, ycoord, zcoord));
}

/**
 *	Factory method using constructor with a vector argument.
 */
Point_ptr Point::create(std::vector<double> &coords)
{
	return Point_ptr(new Point(coords));
}

/**
 *	Returns an array that can be used for affine transformations.
 */
void Point::getMatrix(double matrix[4])
{
	for (int i = 0; i < 3; i++)
	{
		matrix[i] = _getComponent(i);
	}
	matrix[3] = 1;
}

/**
 *	Gets the X component of the point position.
 */
double Point::getX()
{
	return _getComponent(0);
}

/**
 *	Gets the Y component of the point position.
 */
double Point::getY()
{
	return _getComponent(1);
}

/**
 *	Gets the Z component of the point position.
 */
double Point::getZ()
{
	return _getComponent(2);
}

/**
 *	Sets the X component of the point position.
 */
void Point::setX(double value)
{
	return _setComponent(0, value);
}

/**
 *	Sets the Y component of the point position.
 */
void Point::setY(double value)
{
	return _setComponent(1, value);
}

/**
 *	Sets the Z component of the point position.
 */
void Point::setZ(double value)
{
	return _setComponent(2, value);
}