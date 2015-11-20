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
Facet::Facet(Point_ptr points[3], double normals[3])
{
	for (int i = 0; i < 3; i++)
	{
		_points[i] = points[i];
		_normals[i] = normals[i];
	}

	_init();
}

/**
 *	(Private) Constructor taking an array of three points.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Point_ptr points[3])
{
	for (int i = 0; i < 3; i++)
	{
		_points[i] = points[i];
	}

	_calculateNormals();
	_init();
}

void Facet::_init()
{
	_edges[0] = Edge::create(_points[0], _points[1]);
	_edges[1] = Edge::create(_points[1], _points[2]);
	_edges[2] = Edge::create(_points[2], _points[0]);

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
	double nX, nY, nZ, sum;
	Point_ptr p1, p2, p3;

	p1 = _points[0];
	p2 = _points[1];
	p3 = _points[2];

	nX = ((p2->getY() - p1->getY()) * (p3->getZ() - p1->getZ())) - 
		((p3->getY() - p1->getY()) * (p2->getZ() - p1->getZ()));

	nY = ((p2->getZ() - p1->getZ()) * (p3->getX() - p1->getX())) -
		((p2->getX() - p1->getX()) * (p3->getZ() - p1->getZ()));

	nZ = ((p2->getX() - p1->getX()) * (p3->getY() - p1->getY())) -
		((p3->getX() - p1->getX()) * (p2->getY() - p1->getY()));

	nX = pow(nX, 2);
	nY = pow(nY, 2);
	nZ = pow(nZ, 2);

	sum = nX + nY + nZ;

	nX /= sum;
	nY /= sum;
	nZ /= sum;

	nX = sqrt(nX);
	nY = sqrt(nY);
	nZ = sqrt(nZ);

	_normals[0] = nX;
	_normals[1] = nY;
	_normals[2] = nZ;

	cout << nX << " " << nY << " " << nZ << endl;
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

void Facet::_calculateArea()
{
	Edge_ptr* edges = getEdges();
	
	double product, min;
	min = edges[0]->length() * edges[1]->length();
	product = edges[0]->length() * edges[2]->length();

	if (min > product) min = product;
	product = edges[1]->length() * edges[2]->length();

	if (min > product) min = product;

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
 *	== operator overload.
 */
bool operator==(Facet_ptr &f1, Facet_ptr &f2)
{
	return (*f1 == *f2);
}

/**
 *	!= operator overload.
 */
bool operator!=(Facet_ptr &f1, Facet_ptr &f2)
{
	return !(*f1 == *f2);
}

/**
 *	Factory method using the points and normals constructor.
 */
Facet_ptr Facet::create(Point_ptr points[3], double normals[3])
{
	return Facet_ptr(new Facet(points, normals));
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
	return getNormal(0);
}

/**
 *	Get the Y unit normal.
 */
double Facet::getYNormal()
{
	return getNormal(1);
}

/**
 *	Get the Z unit normal.
 */
double Facet::getZNormal()
{
	return getNormal(2);
}

/**
 *	Get the unit normal at the argument index (X = 0, Y = 1, Z = 2).
 */
double Facet::getNormal(int i)
{
	return _normals[i];
}

/**
 *	Get the angle of the facet about the X-axis.
 */
double Facet::getXAng()
{
	return getAng(0);
}

/**
 *	Get the angle of the facet about the Y-axis.
 */
double Facet::getYAng()
{
	return getAng(1);
}

/**
 *	Get the angle of the facet about the Z-axis.
 */
double Facet::getZAng()
{
	return getAng(2);
}

/**
 *	Get the angle of the facet about the axis corresponding to the
 *	argument index (X = 0, Y = 1, Z = 2).
 */
double Facet::getAng(int i)
{
	return _angles[i];
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