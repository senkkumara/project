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

class Edge;
typedef shared_ptr<Edge> Edge_ptr;

class Edge
{
private:
	// Constructors
	Edge(Point_ptr point1, Point_ptr point2);

	// Member variables (private)
	Point_ptr	_points[2];
	double		_angles[3];

	// Member functions (private)
	void		_calculateAngles();
	double		_calculateAngle(double d1, double d2);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Edge &e);
	friend bool operator==(Edge &e1, Edge &e2);
	friend bool operator!=(Edge &e1, Edge &e2);
	friend bool operator==(Edge_ptr &e1, Edge_ptr &e2);
	friend bool operator!=(Edge_ptr &e1, Edge_ptr &e2);

public:
	// Factories
	static Edge_ptr create(Point_ptr point1, Point_ptr point2);

	// Member functions (public)
	void		invert();
	Point_ptr	left();
	Point_ptr	right();
	bool		hasPoint(Point_ptr &point);
	double		getXAng();
	double		getYAng();
	double		getZAng();
	double		getAng(int index);

	// Getters
	Point_ptr*	getPoints();
	double*		getAngles();
};

#endif