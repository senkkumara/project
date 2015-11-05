using namespace std;

#include <iostream>
#include "layer.h"
#include "point.h"

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
 *	point onto it.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layer::Layer(Point_ptr &pnt)
{
	_init();
	_max = pnt->getZ() + _tol;
	_min = pnt->getZ() - _tol;
	add(pnt);
}

/**
 *	(Private) Initialises the member variables.
 */
void Layer::_init()
{
	_tol = 50.0;
	_points = Points::create();
}

/**
 *	Factory method using default constructor.
 */
Layer_ptr Layer::create()
{
	return Layer_ptr(new Layer());
}

/**
 *	Factory method using constructor with a point argument.
 */
Layer_ptr Layer::create(Point_ptr &pnt)
{
	return Layer_ptr(new Layer(pnt));
}

/**
 *	Adds a point to the layer.
 */
void Layer::add(Point_ptr &pnt)
{
	_points->add(pnt);
}

/**
 *	Removes a point from the layer.
 */
void Layer::remove(Point_ptr pnt)
{
	_points->remove(pnt);
}

/**
 *	Returns bool depending on whether a point is on
 *	this layer.
 */
bool Layer::onLayer(Point_ptr &pnt)
{
	return pnt->getZ() <= _max &&
		pnt->getZ() >= _min;
}

/**
 *	Get the tolerance.
 */
double Layer::getTolerance()
{
	return _tol;
}

/**
 *	Get the minimum z-value for this layer.
 */
double Layer::getMin()
{
	return _min;
}

/**
 *	Get the maximum z-value for this layer.
 */
double Layer::getMax()
{
	return _max;
}

/**
 *	Get the points the layer contains.
 */
Points_ptr Layer::getPoints()
{
	return _points;
}

/**
 *	Get the entry edge for the layer.
 */
Edge_ptr Layer::getEntry()
{
	return _entry;
}

/**
 *	Get the exit edge for the layer.
 */
Edge_ptr Layer::getExit()
{
	return _exit;
}

/** 
 *	Set the entry edge of the layer.
 */
void Layer::setEntry(Edge_ptr edge)
{
	_entry = edge;
}

/**
 *	Set the exit edge of the layer.
 */
void Layer::setExit(Edge_ptr edge)
{
	_exit = edge;
}

/**
 *	== operator overload.
 */
bool operator==(Layer &ly1, Layer &ly2)
{
	return true;
}

/**
 *	!= operator overload.
 */
bool operator!=(Layer &ly1, Layer &ly2)
{
	return !(ly1 == ly2);
}