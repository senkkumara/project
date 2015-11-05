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
Edge::Edge(Point_ptr points[2])
{
	_points[0] = points[0];
	_points[1] = points[1];
}

/**
 *	Factory method using constructor with a point array argument.
 */
Edge_ptr Edge::create(Point_ptr points[2])
{
	return Edge_ptr(new Edge(points));
}

/**
 *	
 */
void Edge::_calculateAngles()
{
	Point_ptr pnt1 = _points[0];
	Point_ptr pnt2 = _points[1];

	double dx = pnt2->getX() - pnt1->getX();
	double dy = pnt2->getY() - pnt1->getY();
	double dz = pnt2->getZ() - pnt1->getZ();

	// Store values
	_angle[0] = _calculateAngle(dy, dz);	// anti-clockwise from y;
	_angle[1] = _calculateAngle(dz, dx);	// anti-clockwise from z;
	_angle[2] = _calculateAngle(dx, dy);	// anti-clockwise from x;
}

/**
 *	(Private) Calculates the angle (IN RADIANS) between two
 *	points on a plane.
 */
double Edge::_calculateAngle(double d1, double d2)
{
	double angle = atan2(d1, d2);

	// Correct for negative deltas
	if (d1 < 0)
	{
		angle += M_PI;
	}
	else if (d1 > 0 && d2 < 0)
	{
		angle += 2 * M_PI;
	}

	return angle;
}

Point_ptr* Edge::getPoints()
{
	return _points;
}

double* Edge::getAngle()
{
	return _angle;
}