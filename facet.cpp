using namespace std;

#include "facet.h"

Facet::Facet(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3)
{
	_points[0] = point1;
	_points[1] = point2;
	_points[3] = point3;

	_edges[0] = Edge::create(point1, point2);
	_edges[1] = Edge::create(point2, point3);
	_edges[2] = Edge::create(point3, point1);
}

Facet_ptr Facet::create(Point_ptr &point1, Point_ptr &point2, Point_ptr &point3)
{
	return Facet_ptr(new Facet(point1, point2, point3));
}

bool Facet::isVertical()
{
	return getZNormal() > 0.1;
}

double Facet::getXNormal()
{
	return _normal[0];
}

double Facet::getYNormal()
{
	return _normal[1];
}

double Facet::getZNormal()
{
	return _normal[2];
}

Point_ptr* Facet::getPoints()
{
	return _points;
}

Edge_ptr* Facet::getEdges()
{
	return _edges;
}

double* Facet::getNormal()
{
	return _normal;
}