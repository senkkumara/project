#ifndef EDGE_H
#define EDGE_H

/**
 *	edge.h
 *	-----------------------------------------------------------------------
 *	A edge object represents a 2D/3D line surface conssiting of
 *	two points. It is one of the three geometry objects
 *	used to model an application - also see "facet" and "point".
 */

#include <memory>
#include "point.h"

class Edge;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Edge> Edge_ptr;

class Edge
{
private:
	// Constructors
	Edge(Point_ptr point1, Point_ptr point2);

	// Fields (private)
	Point_ptr	_points[2];
	double		_angles[3];
	double		_length;
	double		_dx;
	double		_dy;
	double		_dz;
	double		_lengthXY;
	double		_lengthXZ;
	double		_lengthYZ;
	double		_minZ;
	double		_maxZ;

	// Methods (private)
	void		_calculateZRange();
	void		_calculateAngles();
	double		_calculateAngle(double d1, double d2);
	void		_calculateLengths();
	double		_getAng(int index);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Edge &e);
	friend std::ostream &operator<<(std::ostream &strm,
		const Edge_ptr &e);

	friend bool operator==(Edge &e1, Edge &e2);
	friend bool operator!=(Edge &e1, Edge &e2);

public:
	// Factories
	static Edge_ptr create(Point_ptr point1, Point_ptr point2);

	// Member functions (public)
	Point_ptr	left();
	Point_ptr	right();
	double		length();
	double		dx();
	double		dy();
	double		dz();
	double		lengthXY();
	double		lengthXZ();
	double		lengthYZ();
	double		getXAng();
	double		getYAng();
	double		getZAng();
	double		getAvgZ();
	void		invert();
	bool		hasPoint(Point_ptr &point);
	Point_ptr*	getPoints();
	double*		getAngles();
	double		getMinZ();
	double		getMaxZ();
};

#endif