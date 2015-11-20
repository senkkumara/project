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
	_geometry = Geometry::create();
	recalculateIfcAngle();
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
void Layer::add(Facet_ptr &facet)
{
	_geometry->add(facet);
}

/**
 *	Removes a facet from the layer.
 */
void Layer::remove(Facet_ptr facet)
{
	_geometry->remove(facet);
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
bool Layer::has(Facet_ptr &facet)
{
	return _geometry->has(facet);
}

/**
 *	Adds a edge to the layer.
 */
void Layer::add(Edge_ptr &edge)
{
	_geometry->add(edge);
}

/**
 *	Removes a edge from the layer.
 */
void Layer::remove(Edge_ptr edge)
{
	_geometry->remove(edge);
}

/**
 *	Returns bool depending on whether a edge is on
 *	this layer.
 */
bool Layer::has(Edge_ptr &edge)
{
	return _geometry->has(edge);
}

/**
 *	Adds a point to the layer.
 */
void Layer::add(Point_ptr &point)
{
	_geometry->add(point);
}

/**
 *	Removes a point from the layer.
 */
void Layer::remove(Point_ptr point)
{
	_geometry->remove(point);
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
bool Layer::has(Point_ptr &point)
{
	return _geometry->has(point);
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
 *	Get the layer type.
 */
LayerType Layer::getType()
{
	return _type;
}

/**
 *	Set the type of the layer.
 */
void Layer::setType(LayerType type)
{
	_type = type;
}