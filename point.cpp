using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "point.h"

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
Point_ptr Point::create(vector<double> &coords)
{
	return Point_ptr(new Point(coords));
}

/**
 *	Gets the X component of the point position.
 */
double Point::getX()
{
	return getComponent(0);
}

/**
 *	Gets the Y component of the point position.
 */
double Point::getY()
{
	return getComponent(1);
}

/**
 *	Gets the Z component of the point position.
 */
double Point::getZ()
{
	return getComponent(2);
}

/**
 *	Gets the component of the point position corresponding
 *	to the provided index (e.g. X has an index of 1).
 */
double Point::getComponent(int index)
{
	return _coords.at(index);
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Point& p)
{
	return strm << '(' << p._coords.at(0) 
				<< ", " << p._coords.at(1)
				<< ", " << p._coords.at(2)
				<< ')' << endl;
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