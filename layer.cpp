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
	init();
}

/**
 *	(Private) Constructs a layer and inserts an argument
 *	point onto it.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layer::Layer(Point_ptr &pnt)
{
	init();
	add(pnt);
	setMax(pnt->getZ() + _tol);
	setMin(pnt->getZ() - _tol);
}

/**
 *	(Private) Initialises the member variables.
 */
void Layer::init()
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
void Layer::remove(Point_ptr &pnt)
{
	//TODO: implement function
	/*for (int i = 0; i < _pnts.size(); i++)
	{
		if (*pnt == *_pnts.at(i))
		{
			_pnts.erase(_pnts.begin + i - 1);
		}
	}*/
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
 *	Set the minimum z-value for this layer.
 */
void Layer::setMin(double min)
{
	_min = min;
}

/**
 *	Set the maximum z-value for this layer.
 */
void Layer::setMax(double max)
{
	_max = max;
}