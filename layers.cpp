using namespace std;

#include <iostream>
#include "layers.h"
#include "layer.h"
#include "point.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layers::Layers()
{

}

/**
 *	(Private) Constructs a vector of layers from a vector
 *	containing points.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layers::Layers(Points_ptr &points)
{
	Point_ptr point;
	Layer_ptr layer;

	_items.push_back(Layer::create(points->get(0)));

	for (int i = 1; i < points->size(); i++)
	{
		point = points->get(i);
		layer = findLayer(point);
		if (layer)
		{
			layer->add(point);
		}
		else
		{
			_items.push_back(Layer::create(point));
		}
		
	}
}

/**
 *	Factory method using default constructor.
 */
Layers_ptr Layers::create()
{
	return Layers_ptr(new Layers());
}

/**
 *	Factory method using constructor with points argument.
 */
Layers_ptr Layers::create(Points_ptr &points)
{
	return Layers_ptr(new Layers(points));
}

/**
 *	Add a layer to the list.
 */
void Layers::add(Layer_ptr &layer)
{
	_items.push_back(layer);
}

/**
 *	Remove a layer from the list.
 */
void Layers::remove(Layer_ptr &layer)
{
	//TODO: implement method.
}

/**
 *	Retrieve a layer by index.
 */
Layer_ptr Layers::get(int index)
{
	return _items.at(index);
}

/**
 *	Find the layer that contains the argument part.
 */
Layer_ptr Layers::findLayer(Point_ptr &pnt)
{
	for (int j = _items.size() - 1; j >= 0; j--)
	{
		Layer_ptr lyr = _items.at(j);
		if (lyr->onLayer(pnt))
		{
			return lyr;
		}
	}

	return nullptr;
}

/**
 *	Return the size of the list.
 */
int Layers::size()
{
	return _items.size();
}

/**
 *	Order the layers by Z distance.
 */
void Layers::sort()
{
	
}

/**
 *	Removes the additional points in the first and last layers -
 *	these layers should only contain two points.
 */
void Layers::trim()
{

}

/**
 *	Checks if the boundaries of any layers in the list overlap.
 */
bool Layers::hasOverlaps()
{
	sort();
	if (size() < 2) return false;

	for (int i = 1; i < size(); i++)
	{
		if (get(i)->getMin() < get(i - 1)->getMax())
		{
			return true;
		}
	}

	return false;
}

/**
 *	Get the vector containing the layers.
 */
vector<Layer_ptr> Layers::getItems()
{
	return _items;
}