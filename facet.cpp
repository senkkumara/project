/**
 *	facet.cpp
 *	-----------------------------------------------------------------------
 *	See "facet.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include "facet.h"
#include <iostream>
#include "edges.h"
#include "exceptions.h"

/**
 *	(Private) Constructor taking an array of three points and the normals.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Point_ptr points[3], Edge_ptr edges[3], double normals[3])
{
	for (int i = 0; i < 3; i++)
	{
		_points[i] = points[i];
		_edges[i] = edges[i];
		_normals[i] = normals[i];
	}

	_init();
}

/**
 *	(Private) Carries out functions that should be common to all
 *	constructors.
 */
void Facet::_init()
{
	_calculateAngles();
	_calculateArea();
	_calculateZRange();
}

/**
 *	(Private) Calculates the unit normal vector for the surface from
 *	the three vertices.
 */
void Facet::_calculateNormals()
{
	double n[3], sum = 0;
	Point_ptr p[3];

	// Get components
	for (int i = 0; i < 3; i++)
	{
		p[i] = _points[i];
	}
	
	// Calculate normal vector
	n[0] = ((p[1]->getY() - p[0]->getY()) * (p[2]->getZ() - p[0]->getZ())) - 
		((p[2]->getY() - p[0]->getY()) * (p[1]->getZ() - p[0]->getZ()));

	n[1] = ((p[1]->getZ() - p[0]->getZ()) * (p[2]->getX() - p[0]->getX())) -
		((p[1]->getX() - p[0]->getX()) * (p[2]->getZ() - p[0]->getZ()));

	n[2] = ((p[1]->getX() - p[0]->getX()) * (p[2]->getY() - p[0]->getY())) -
		((p[2]->getX() - p[0]->getX()) * (p[1]->getY() - p[0]->getY()));

	// Convert to unit vector:
	//	1. Sum square of components
	//	2. Divide component by sum
	//	3. Square root component
	//
	for (int i = 0; i < 3; i++)
	{
		n[i] = pow(n[i], 2);
		sum += n[i];
	}

	for (int i = 0; i < 3; i++)
	{
		n[i] /= sum;
		_normals[i] = sqrt(n[i]);
	}
	
}

/**
 *	(Private) Calculate the yaw, pitch and roll of the facet in
 *	3D space.
 */
void Facet::_calculateAngles()
{
	double dx = getXNormal();
	double dy = getYNormal();
	double dz = getZNormal();

	// Store values
	_angles[0] = _calculateAngle(dy, dz);	// anti-clockwise from y;
	_angles[1] = _calculateAngle(dz, dx);	// anti-clockwise from z;
	_angles[2] = _calculateAngle(dx, dy);	// anti-clockwise from x;
}

/**
 *	(Private) Calculates the area of the facet.
 */
void Facet::_calculateArea()
{
	Edge_ptr* edges = getEdges();
	
	// Look for the lowest product of two edge lengths -
	// this will correspond to the shortest edges
	double product, min;
	min = edges[0]->length() * edges[1]->length();
	product = edges[0]->length() * edges[2]->length();

	if (min > product) min = product;
	product = edges[1]->length() * edges[2]->length();

	if (min > product) min = product;

	// Divide by 2 to get the area
	_area = product / 2;
}

/**
 *	(Private) Calculates the angle (IN RADIANS) of the facet in a
 *	3D space.
 */
double Facet::_calculateAngle(double d1, double d2)
{
	return atan2(d2, d1);
}

/**
 *	(Private) Calculates the minimum and maximum Z-height of the 
 *	facet.
 */
void Facet::_calculateZRange()
{
	_minZ = _points[0]->getZ();
	_maxZ = _minZ;

	double z;
	for (int i = 1; i < 3; i++)
	{
		z = _points[i]->getZ();
		if (z < _minZ)
		{
			_minZ = z;
			continue;
		}

		if (z > _maxZ)
		{
			_maxZ = z;
		}
	}
}

/**
 *	Get the unit normal at the argument index (X = 0, Y = 1, Z = 2).
 */
double Facet::_getNormal(int i)
{
	return _normals[i];
}

/**
 *	Get the angle of the facet about the axis corresponding to the
 *	argument index (X = 0, Y = 1, Z = 2).
 */
double Facet::_getAng(int i)
{
	return _angles[i];
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Facet &f)
{
	return strm << "Point 1: " << f._points[0] << ", "
				<< "Point 2: " << f._points[1] << ", "
				<< "Point 3: " << f._points[2] << endl;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Facet_ptr &f)
{
	return strm << *f;
}

/**
 *	== operator overload.
 */
bool operator==(Facet &f1, Facet &f2)
{
	for (int i = 0; i < 3; i++)
	{
		if (!( f1.hasEdge(f2.getEdge(i))))
		{
			return false;
		}
	}

	return true;
}

/**
 *	!= operator overload.
 */
bool operator!=(Facet &f1, Facet &f2)
{
	return !(f1 == f2);
}

/**
 *	Factory method using the points and normals constructor.
 */
Facet_ptr Facet::create(Point_ptr points[3], Edge_ptr edges[3], double normals[3])
{
	return Facet_ptr(new Facet(points, edges, normals));
}

/**
 *	Returns a boolean depending on whether the surface is
 *	approximately vertical.
 */
bool Facet::isVertical()
{
	return ((getMaxZ() - getMinZ()) > 50);
}

/**
 *	Returns a boolean depending on whether the surface is
 *	approximately horizontal.
 */
bool Facet::isHorizontal()
{
	return ! isVertical();
}

/**
 *	Returns a boolean depending on whether the argument point
 *	is one of the vertices of the facet.
 */
bool Facet::hasPoint(Point_ptr &point)
{
	for (int i = 0; i < 3; i++)
	{
		if (getPoint(i) == point)
		{
			return true;
		}
	}

	return false;
}

/**
 *	Returns a boolean depending on whether the argument edge
 *	is one of those that form the facet.
 */
bool Facet::hasEdge(Edge_ptr &edge)
{
	for (int i = 0; i < 3; i++)
	{
		if (getEdge(i) == edge)
		{
			return true;
		}
	}

	return false;
}

/**
 *	Get the edge corresponding to the argument index.
 */
Edge_ptr Facet::getEdge(int i)
{
	return _edges[i];
}

/**
 *	Get the point corresponding to the argument index.
 */
Point_ptr Facet::getPoint(int i)
{
	return _points[i];
}

/**
 *	Get the X unit normal.
 */
double Facet::getXNormal()
{
	return _getNormal(0);
}

/**
 *	Get the Y unit normal.
 */
double Facet::getYNormal()
{
	return _getNormal(1);
}

/**
 *	Get the Z unit normal.
 */
double Facet::getZNormal()
{
	return _getNormal(2);
}

/**
 *	Get the angle of the facet about the X-axis.
 */
double Facet::getXAng()
{
	return _getAng(0);
}

/**
 *	Get the angle of the facet about the Y-axis.
 */
double Facet::getYAng()
{
	return _getAng(1);
}

/**
 *	Get the angle of the facet about the Z-axis.
 */
double Facet::getZAng()
{
	return _getAng(2);
}

/**
 *	Return the average height of the facet - take as an average of the
 *	height of each of the points.
 */
double Facet::getAvgZ()
{
	return (_minZ + _maxZ) / 2;
}

/**
 *	Get the points that comprise the vertices of the facet.
 */
Point_ptr* Facet::getPoints()
{
	return _points;
}

/**
 *	Get the edges that comprise the edegs of the facet.
 */
Edge_ptr* Facet::getEdges()
{
	return _edges;
}

/**
 *	Get the unit normal components.
 */
double* Facet::getNormals()
{
	return _normals;
}

/**
 *	Get minimum Z value.
 */
double Facet::getMinZ()
{
	return _minZ;
}

/**
 *	Get maximum Z value.
 */
double Facet::getMaxZ()
{
	return _maxZ;
}