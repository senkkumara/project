using namespace std;

#include <iostream>
#include "layer.h"
#include "point.h"

Layer::Layer(Point_ptr &pnt)
{
	double tol = 50.0;
	_points = Points::create();

	add(pnt);
	setMax(pnt->getZ() + tol);
	setMin(pnt->getZ() - tol);
}

Layer::~Layer()
{
	//TODO: Add destructor
}

Layer_ptr Layer::create(Point_ptr &pnt)
{
	return Layer_ptr(new Layer(pnt));
}

void Layer::add(Point_ptr &pnt)
{
	_points->add(pnt);
}

void Layer::remove(Point_ptr &pnt)
{
	/*for (int i = 0; i < _pnts.size(); i++)
	{
		if (*pnt == *_pnts.at(i))
		{
			_pnts.erase(_pnts.begin + i - 1);
		}
	}*/
}

bool Layer::onLayer(Point_ptr &pnt)
{
	return pnt->getZ() <= _max &&
		pnt->getZ() >= _min;
}

void Layer::setMin(double min)
{
	_min = min;
}

void Layer::setMax(double max)
{
	_max = max;
}

double Layer::getMin()
{
	return _min;
}

double Layer::getMax()
{
	return _max;
}

Points_ptr Layer::getPoints()
{
	return _points;
}