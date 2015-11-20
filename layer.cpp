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