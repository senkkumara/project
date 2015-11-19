#ifndef FACET_H
#define FACET_H

/**
 *	facet.h
 *	-----------------------------------------------------------------------
 *	A facet object represents a 2D/3D triangular surface consisting of
 *	three points and three edges. It is one of the three geometry objects
 *	used to model an application - also see "edge" and "point".
 */

using namespace std;

#include <memory>
#include "point.h"
#include "points.h"
#include "edge.h"

class Facet;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Facet> Facet_ptr;

class Facet
{
private:
	// Constructors
	Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3);
	Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3,
		Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3);

	Facet(Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3);
	Facet(Edge_ptr &edge1, Edge_ptr &edge2, Edge_ptr &edge3, bool check);

	// Member variables (private)
	Point_ptr	_points[3];
	Edge_ptr	_edges[3];
	double		_normals[3];
	double		_angles[3];
	double		_maxZ;
	double		_minZ;

	// Member functions (private)
	void	_calculateAngles();
	double	_calculateAngle(double d1, double d2);
	void	_calculateZRange();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Facet &f);
	friend std::ostream &operator<<(std::ostream &strm,
		const Facet_ptr &f);

	friend bool operator==(Facet &cF1, Facet &cF2);
	friend bool operator!=(Facet &cF1, Facet &cF2);
	friend bool operator==(Facet_ptr &cF1, Facet_ptr &cF2);
	friend bool operator!=(Facet_ptr &cF1, Facet_ptr &cF2);

public:
	// Factories
	static Facet_ptr create(Point_ptr &point1, Point_ptr &point2,
		Point_ptr &point3);

	static Facet_ptr create(Point_ptr &point1, Point_ptr &point2,
		Point_ptr &point3, Edge_ptr &edge1, Edge_ptr &edge2,
		Edge_ptr &edge3);

	static Facet_ptr create(Edge_ptr &edge1, Edge_ptr &edge2,
		Edge_ptr &edge3);

	static Facet_ptr create(Edge_ptr &edge1, Edge_ptr &edge2,
		Edge_ptr &edge3, bool check);

	// Member functions (public)
	bool		isVertical(double tol);
	bool		hasPoint(Point_ptr &point);
	bool		hasEdge(Edge_ptr &edge);
	Edge_ptr	getEdge(int i);
	Point_ptr	getPoint(int i);
	double		getXNormal();
	double		getYNormal();
	double		getZNormal();
	double		getNormal(int i);
	double		getXAng();
	double		getYAng();
	double		getZAng();
	double		getAng(int i);

	// Getters
	Point_ptr*	getPoints();
	Edge_ptr*	getEdges();
	double*		getNormals();
	double		getMinZ();
	double		getMaxZ();
};

#endif