#ifndef FACET_H
#define FACET_H

using namespace std;

#include <memory>
#include "point.h"
#include "points.h"
#include "edge.h"

class Facet;
typedef shared_ptr<Facet> Facet_ptr;

class Facet
{
private:
	// Constructors
	Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3);

	// Member variables (private)
	Point_ptr	_points[3];
	Edge_ptr	_edges[3];
	double		_normal[3];

public:
	// Factories
	static Facet_ptr create(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3);

	// Member functions (public)
	bool		isVertical();
	double		getXNormal();
	double		getYNormal();
	double		getZNormal();

	// Getters
	Point_ptr*	getPoints();
	Edge_ptr*	getEdges();
	double*		getNormal();
};

#endif