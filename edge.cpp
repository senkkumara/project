using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>
#include "edge.h"
#include <iostream>

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
	_calculateAngles();
}

/**
 *	Factory method using constructor with a point array argument.
 */
Edge_ptr Edge::create(Point_ptr point1, Point_ptr point2)
{
	return Edge_ptr(new Edge(point1, point2));
}

/**
 *	(Private) Calculate the yaw, pitch and roll of the edge in
 *	3D space.
 */
void Edge::_calculateAngles()
{
	Point_ptr pnt1 = _points[0];
	Point_ptr pnt2 = _points[1];

	double dx = pnt2->getX() - pnt1->getX();
	double dy = pnt2->getY() - pnt1->getY();
	double dz = pnt2->getZ() - pnt1->getZ();

	// Store values
	_angles[0] = _calculateAngle(dy, dz);	// anti-clockwise from y;
	_angles[1] = _calculateAngle(dz, dx);	// anti-clockwise from z;
	_angles[2] = _calculateAngle(dx, dy);	// anti-clockwise from x;
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
 *	Return the angle about the X-axis (+ive y-axis forms origin)
 */
double Edge::angX()
{
	return ang(0);
}

/**
 *	Return the angle about the Y-axis (+ive z-axis forms origin)
 */
double Edge::angY()
{
	return ang(1);
}

/**
 *	Return the angle about the Z-axis (+ive x-axis forms origin)
 */
double Edge::angZ()
{
	return ang(2);
}

/**
 *	Return the angle about the axis corresponding to an index -
 *	e.g. X = 0, Y = 1, Z = 2
 */
double Edge::ang(int index = 0)
{
	return getAngles()[index];
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
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edge &e)
{
	return strm << "Left: " << e._points[0] << ", "
				<< "Right: " << e._points[1] << endl;
}

/**
 *	== operator overload.
 */
bool operator==(Edge &e1, Edge &e2)
{
	Point_ptr p11 = e1.left();
	Point_ptr p12 = e1.right();
	Point_ptr p21 = e2.left();
	Point_ptr p22 = e2.right();

	return ((*p11 == *p21 || *p11 == *p22) &&
			(*p12 == *p21 || *p12 == *p22) &&
			(*p11 != *p12) && (*p21 != *p22));
}

/**
 *	!= operator overload.
 */
bool operator!=(Edge &e1, Edge &e2)
{
	return !(e1 == e2);
}