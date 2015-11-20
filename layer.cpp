/**
 *	layer.cpp
 *	-----------------------------------------------------------------------
 *	See "layer.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include "layer.h"
#include <iostream>
#include "edge.h"
#include "point.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layer::Layer()
{
	_init();
}

/**
 *	(Private) Constructs a layer and inserts an argument
 *	facet onto it.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layer::Layer(Facet_ptr &facet)
{
	_init();
	_maxHeight = facet->getMaxZ() + _tol;
	_minHeight = facet->getMinZ() - _tol;

	add(facet);
}

/**
 *	(Private) Initialises the member variables.
 */
void Layer::_init()
{
	_tol = 35.0;
	_facets = Facets::create();
	_edges = Edges::create();
	_points = Points::create();
	_setIfcAngle();
}

/**
 *	Calculate the angle between the entry and the exit of the layer.
 *	The origin of the rotation is the entry edge.
 */
void Layer::_setIfcAngle()
{
	if (_entry && _exit)
	{
		Point_ptr origin = _entry->left();
		double x1, y1,x2, y2, xOr, yOr, rot,
			xDash1, yDash1, xDash2, yDash2, dx, dy;
		
		// Get origin (distance to translate by)
		xOr = origin->getX();
		yOr = origin->getY();

		// Get angle to rotate by
		rot = _entry->getZAng();

		// Get pre-transformed points
		x1 = _exit->left()->getX();
		y1 = _exit->left()->getY();
		x2 = _exit->right()->getX();
		y2 = _exit->right()->getY();

		// Translate and rotate the points about the origin
		xDash1 = ((x1 - xOr) * cos(rot)) + ((y1 - yOr) * sin(rot));
		xDash2 = ((x2 - xOr) * cos(rot)) + ((y2 - yOr) * sin(rot));
		yDash1 = ((y1 - xOr) * cos(rot)) - ((x1 - yOr) * sin(rot));
		yDash2 = ((y2 - xOr) * cos(rot)) - ((x2 - yOr) * sin(rot));

		// Calculate the deltas
		dx = xDash2 - xDash1;
		dy = yDash2 - yDash1;

		// Calculate angle
		_ifcAngle = atan2(dy, dx);
	}
	else
	{
		// Must be first or last layer, therefore there is no angle since
		// the layer only has an exit or entry respectively.
		_ifcAngle = 0;
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Layer &layer)
{
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Layer_ptr &layer)
{
	return strm << *layer;
}

/**
 *	< operator overload.
 */
bool operator<(Layer &layer1, Layer &layer2)
{
	return true;
}

/**
 *	<= operator overload.
 */
bool operator<=(Layer &layer1, Layer &layer2)
{
	return true;
}

/**
 *	== operator overload.
 */
bool operator==(Layer &layer1, Layer &layer2)
{
	return true;
}

/**
 *	!= operator overload.
 */
bool operator!=(Layer &layer1, Layer &layer2)
{
	return !(layer1 == layer2);
}

/**
 *	>= operator overload.
 */
bool operator>=(Layer &layer1, Layer &layer2)
{
	return true;
}

/**
 *	> operator overload.
 */
bool operator>(Layer &layer1, Layer &layer2)
{
	return true;
}

/**
 *	< operator overload.
 */
bool operator<(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 < *layer2);
}

/**
 *	<= operator overload.
 */
bool operator<=(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 <= *layer2);
}

/**
 *	== operator overload.
 */
bool operator==(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 == *layer2);
}

/**
 *	!= operator overload.
 */
bool operator!=(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 != *layer2);
}

/**
 *	>= operator overload.
 */
bool operator>=(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 >= *layer2);
}

/**
 *	> operator overload.
 */
bool operator>(Layer_ptr &layer1, Layer_ptr &layer2)
{
	return (*layer1 > *layer2);
}

/**
 *	Factory method using default constructor.
 */
Layer_ptr Layer::create()
{
	return Layer_ptr(new Layer());
}

/**
 *	Factory method using constructor with a facet argument.
 */
Layer_ptr Layer::create(Facet_ptr &facet)
{
	return Layer_ptr(new Layer(facet));
}

/**
 *	Adds a facet to the layer.
 */
void Layer::add(Facet_ptr &point)
{
	_facets->add(point);
}

/**
 *	Removes a facet from the layer.
 */
void Layer::remove(Facet_ptr point)
{
	_facets->remove(point);
}

/**
 *	Returns bool depending on whether a facet should be on
 *	this layer.
 */
bool Layer::onLayer(Facet_ptr &facet)
{
	return facet->getMaxZ() <= _maxHeight &&
		facet->getMinZ() >= _minHeight;
}

/**
 *	Returns bool depending on whether a facet is on
 *	this layer.
 */
bool Layer::hasFacet(Facet_ptr &facet)
{
	for (int i = 0; i < _facets->size(); i++)
	{
		if (_facets->get(i) == facet)
		{
			return true;
		}
	}

	return false;
}

/**
 *	Adds a edge to the layer.
 */
void Layer::add(Edge_ptr &edge)
{
	_edges->add(edge);
}

/**
 *	Removes a edge from the layer.
 */
void Layer::remove(Edge_ptr edge)
{
	_edges->remove(edge);
}

/**
 *	Returns bool depending on whether a edge is on
 *	this layer.
 */
bool Layer::hasEdge(Edge_ptr &edge)
{
	for (int i = 0; i < _edges->size(); i++)
	{
		if (_edges->get(i) == edge)
		{
			return true;
		}
	}

	return false;
}

/**
 *	Adds a point to the layer.
 */
void Layer::add(Point_ptr &point)
{
	_points->add(point);
}

/**
 *	Removes a point from the layer.
 */
void Layer::remove(Point_ptr point)
{
	_points->remove(point);
}

/**
 *	Returns bool depending on whether a point should be on
 *	this layer.
 */
bool Layer::onLayer(Point_ptr &point)
{
	return point->getZ() <= _maxHeight &&
		point->getZ() >= _minHeight;
}

/**
 *	Returns bool depending on whether a point is on
 *	this layer.
 */
bool Layer::hasPoint(Point_ptr &point)
{
	for (int i = 0; i < _points->size(); i++)
	{
		if (_points->get(i) == point)
		{
			return true;
		}
	}

	return false;
}

/**
 *	Swaps the points at the ends of the edges that form the entry to the
 *	layer.
 *
 *	Use this instead of point->invert() to ensure the layer angle is
 *	recalculated.
 */
void Layer::invertEntry()
{
	_entry->invert();
	_setIfcAngle();
}

/**
 *	Swaps the points at the ends of the edges that form the exit to the
 *	layer.
 *
 *	Use this instead of point->invert() to ensure the layer angle is
 *	recalculated.
 */
void Layer::invertExit()
{
	_exit->invert();
	_setIfcAngle();
}

/**
 *	Get the entry edge for the layer.
 */
Edge_ptr Layer::entry()
{
	return _entry;
}

/**
 *	Get the exit edge for the layer.
 */
Edge_ptr Layer::exit()
{
	return _exit;
}

/**
 *	Get the tolerance.
 */
double Layer::getHeightTol()
{
	return _tol;
}

/**
 *	Get the minimum z-value for this layer.
 */
double Layer::getMinHeight()
{
	return _minHeight;
}

/**
 *	Get the maximum z-value for this layer.
 */
double Layer::getMaxHeight()
{
	return _maxHeight;
}

/**
 *	Get the facets the layer contains.
 */
Facets_ptr Layer::getFacets()
{
	return _facets;
}

/**
 *	Get the Edges the layer contains.
 */
Edges_ptr Layer::getEdges()
{
	return _edges;
}

/**
 *	Get the points the layer contains.
 */
Points_ptr Layer::getPoints()
{
	return _points;
}

/**
 *	Get the Interface angle for the layer;
 */
double Layer::getIfcAngle()
{
	return _ifcAngle;
}

/**
 *	Get the layer type.
 */
LayerType Layer::getType()
{
	return _type;
}

/** 
 *	Set the entry edge of the layer.
 */
void Layer::setEntry(Edge_ptr edge)
{
	_entry = edge;
	_setIfcAngle();
}

/**
 *	Set the exit edge of the layer.
 */
void Layer::setExit(Edge_ptr edge)
{
	_exit = edge;
	_setIfcAngle();
}

/**
 *	Set the type of the layer.
 */
void Layer::setType(LayerType type)
{
	_type = type;
}