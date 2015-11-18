/**
 *	facet.cpp
 *	-----------------------------------------------------------------------
 *	See "facet.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include "facet.h"
#include "exceptions.h"

/**
 *	(Private) Constructor taking a series of three points as an argument. Edges
 *	are constructed from these points, joining the first to the second,
 *	second to third and third to first.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3)
{
	_points[0] = point1;
	_points[1] = point2;
	_points[3] = point3;

	_edges[0] = Edge::create(point1, point2);
	_edges[1] = Edge::create(point2, point3);
	_edges[2] = Edge::create(point3, point1);
}

/**
 *	(Private) Constructs a facet from three points and three edges
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3,
			 Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3)
{
	_points[0] = point1;
	_points[1] = point2;
	_points[3] = point3;

	_edges[0] = edge1;
	_edges[1] = edge2;
	_edges[2] = edge3;
}

/**
 *	(Private) Constructs a facet from three edges. It does not
 *	check that the edges provided are correctly oriented and
 *	form a closed polygon!
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3)
{
	_points[0] = edge1->left();
	_points[1] = edge1->right();
	_points[3] = edge2->left();

	_edges[0] = edge1;
	_edges[1] = edge2;
	_edges[2] = edge3;
}

/**
 *	(Private) Constructs a facet from three edges checking they form
 *	a closed polygon.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facet::Facet(Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3, bool check)
{
	if (check) {
		// Check join between edges 1 and 2
		Point_ptr point = edge1->right();

		if (edge3->hasPoint(point))
		{
			Edge_ptr tmp = edge2;
			edge2 = edge3;
			edge3 = tmp;
		}
		else
		{
			if (! edge2->hasPoint(point))
			{
				throw 1;	// No matching point in edge 2 or 3
			}
		}

		// Edge 2 is flipped
		if (edge2->left() != point)
		{
			edge2->invert();
		}

		// Check join between edges 2 and 3
		point = edge2->right();

		if (! edge3->hasPoint(point))
		{
			throw 1;	// No matching point in edge 3
		}

		if (edge3->left() != point)
		{
			edge3->invert();
		}

		// Check the facet closes
		if (edge1->left() != edge3->right())
		{
			throw 1;	// Loop does not close
		}
	}

	Facet(edge1, edge2, edge3);
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
 *	(Private) Calculates the angle (IN RADIANS) of the facet in a
 *	3D space.
 */
double Facet::_calculateAngle(double d1, double d2)
{
	return atan2(d2, d1);
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
 *	Factory method using the points only constructor.
 */
Facet_ptr Facet::create(Point_ptr &point1, Point_ptr &point2,
						Point_ptr &point3)
{
	return Facet_ptr(new Facet(point1, point2, point3));
}

/**
 *	Factory method using the points and edges constructor.
 */
Facet_ptr Facet::create(Point_ptr &point1, Point_ptr &point2,
						Point_ptr &point3, Edge_ptr &edge1,
						Edge_ptr &edge2, Edge_ptr &edge3)
{
	return Facet_ptr(new Facet(point1, point2, point3, edge1,
		edge2, edge3));
}

/**
 *	Factory method using the edges only constructor without
 *	checking.
 */
Facet_ptr Facet::create(Edge_ptr &edge1, Edge_ptr &edge2,
						Edge_ptr &edge3)
{
	return Facet_ptr(new Facet(edge1, edge2, edge3));
}

/**
 *	Factory method using the edges only constructor with
 *	checking.
 */
Facet_ptr Facet::create(Edge_ptr &edge1, Edge_ptr &edge2,
						Edge_ptr &edge3, bool check)
{
	return Facet_ptr(new Facet(edge1, edge2, edge3, check));
}

/**
 *	Returns a boolean depending on whether the surface is
 *	approximately vertical.
 */
bool Facet::isVertical(double tol = 0.1)
{
	return getZNormal() > tol;
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