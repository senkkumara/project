/**
 *	edge.cpp
 *	-----------------------------------------------------------------------
 *	See "edge.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include "edge.h"
#include <iostream>
#include <math.h>

/**
 *	(Private) Constructor taking an argument of an array
 *	containing the two points that make up the ends of the
 *	edge.
 *
 *	Do not use this directly, use the provided factory method.
 */
Edge::Edge(Point_ptr point1, Point_ptr point2)
{
	_points[0] = point1;
	_points[1] = point2;
	_calculateZRange();
	_calculateLengths();
	_calculateAngles();
}

/**
 *	(Private) Calculates the minimum and maximum Z-height of the 
 *	Edge.
 */
void Edge::_calculateZRange()
{
	_minZ = _points[0]->getZ();
	_maxZ = _minZ;

	double z = _points[1]->getZ();
	if (z < _minZ)
	{
		_minZ = z;
	}

	if (z > _maxZ)
	{
		_maxZ = z;
	}
}

/**
 *	(Private) Calculate the yaw, pitch and roll of the edge in
 *	3D space.
 */
void Edge::_calculateAngles()
{
	Point_ptr pnt1 = _points[0];
	Point_ptr pnt2 = _points[1];

	// Store values
	_angles[0] = _calculateAngle(_d[1], _d[2]);	// anti-clockwise from y;
	_angles[1] = _calculateAngle(_d[2], _d[0]);	// anti-clockwise from z;
	_angles[2] = _calculateAngle(_d[0], _d[1]);	// anti-clockwise from x;
}

/**
 *	(Private) Calculates the angle (IN RADIANS) between two
 *	points on a plane.
 */
double Edge::_calculateAngle(double d1, double d2)
{
	return atan2(d2, d1);
}

/**
 *	(Private) Calculate the various forms of length field for the edge.
 */
void Edge::_calculateLengths()
{
	Point_ptr pnt1 = _points[0];
	Point_ptr pnt2 = _points[1];

	_d[0] = pnt2->getX() - pnt1->getX();
	_d[1] = pnt2->getY() - pnt1->getY();
	_d[2] = pnt2->getZ() - pnt1->getZ();

	_length = sqrt(pow(_d[0], 2) + pow(_d[1], 2) + pow(_d[2], 2));
	_lengthXY = sqrt(pow(_d[0], 2) + pow(_d[1], 2));
	_lengthXZ = sqrt(pow(_d[0], 2) + pow(_d[2], 2));
	_lengthYZ = sqrt(pow(_d[1], 2) + pow(_d[2], 2));
}

/**
 *	(Private) Return the angle about the axis corresponding to an index -
 *	e.g. X = 0, Y = 1, Z = 2
 */
double Edge::_getAng(int index = 0)
{
	return getAngles()[index];
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edge &e)
{
	return strm << "Left: " << e._points[0] << ", "
				<< "Right: " << e._points[1] << endl;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edge_ptr &e)
{
	return strm << *e;
}

/**
 *	== operator overload.
 */
bool operator==(Edge &e1, Edge &e2)
{
	return (e2.hasPoint(e1.left()) && e2.hasPoint(e1.right()));
}

/**
 *	!= operator overload.
 */
bool operator!=(Edge &e1, Edge &e2)
{
	return !(e1 == e2);
}

/**
 *	Factory method using constructor with a point array argument.
 */
Edge_ptr Edge::create(Point_ptr point1, Point_ptr point2)
{
	return Edge_ptr(new Edge(point1, point2));
}

/**
 *	Return the "left" point of the edge - as read from a person
 *	walking up the stairs (assuming it has been set up correctly!).
 */
Point_ptr Edge::left()
{
	return _points[0];
}

/**
 *	Return the "right" point of the edge - as read from a person
 *	walking up the stairs (assuming it has been set up correctly!).
 */
Point_ptr Edge::right()
{
	return _points[1];
}

/**
 *	Return the length of the edge.
 */
double Edge::length()
{
	return _length;
}

/**
 *	Return the x-component of the vector joining the two points.
 */
double Edge::dx()
{
	return _d[0];
}

/**
 *	Return the y-component of the vector joining the two points.
 */
double Edge::dy()
{
	return _d[1];
}

/**
 *	Return the z-component of the vector joining the two points.
 */
double Edge::dz()
{
	return _d[2];
}

/**
 *	Return length of the vector joining the two points on the X-Y plane.
 */
double Edge::lengthXY()
{
	return _lengthXY;
}

/**
 *	Return length of the vector joining the two points on the X-Z plane.
 */
double Edge::lengthXZ()
{
	return _lengthXZ;
}

/**
 *	Return length of the vector joining the two points on the Y-Z plane.
 */
double Edge::lengthYZ()
{
	return _lengthYZ;
}

/**
 *	Return the angle about the X-axis (+ive y-axis forms origin)
 */
double Edge::getXAng()
{
	return _getAng(0);
}

/**
 *	Return the angle about the Y-axis (+ive z-axis forms origin)
 */
double Edge::getYAng()
{
	return _getAng(1);
}

/**
 *	Return the angle about the Z-axis (+ive x-axis forms origin)
 */
double Edge::getZAng()
{
	return _getAng(2);
}

/**
 *	Return the average height of the edge - take as an average of the
 *	height of each of the points.
 */
double Edge::getAvgZ()
{
	return (_minZ + _maxZ) / 2;
}

/**
 *	Swap the ends of the edge.
 */
void Edge::invert()
{
	Point_ptr tmp = left();
	_points[0] = right();
	_points[1] = tmp;

	// Recalculate angles
	_calculateAngles();
}

/**
 *	Returns boolean depending on whether an argument point is
 *	at either end of the edge.
 */
bool Edge::hasPoint(Point_ptr &point)
{
	return (*point == *left() || *point == *right());
}

/**
 *	Get the points that the edge comprises of.
 */
Point_ptr* Edge::getPoints()
{
	return _points;
}

/**
 *	Get the angles of the edge in 3D space.
 */
double* Edge::getAngles()
{
	return _angles;
}

/**
 *	Get the maximum height of the edge.
 */
double Edge::getMaxZ()
{
	return _maxZ;
}

/**
 *	Get the minimum height of the edge.
 */
double Edge::getMinZ()
{
	return _minZ;
}