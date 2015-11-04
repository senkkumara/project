using namespace std;

#include <iostream>
#include "layers.h"
#include "layer.h"
#include "point.h"

Layers::Layers(Points_ptr &pnts)
{
	_items.push_back(Layer::create(pnts->get(0)));

	for (int i = 1; i < pnts->size(); i++)
	{
		Point_ptr pnt = pnts->get(i);
		Layer_ptr lyr = findLayer(pnt);
		if (lyr)
		{
			lyr->add(pnt);
		}
		else
		{
			_items.push_back(Layer::create(pnts->get(i)));
		}
		
	}
}

Layer_ptr Layers::findLayer(Point_ptr pnt)
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

Layers::~Layers()
{
	//TODO: Add destructor
}

Layers_ptr Layers::create(Points_ptr &pnts)
{
	return Layers_ptr(new Layers(pnts));
}

vector<Layer_ptr> Layers::getItems()
{
	return _items;
}

/**
 *	Add a layer to the list.
 */
void Layers::add(Layer_ptr lyr)
{
	_items.push_back(lyr);
}

/**
 *	Remove a layer from the list.
 */
void Layers::remove(Layer_ptr lyr)
{

}

/**
 *	Retrieve a layer by index.
 */
Layer_ptr Layers::get(int index)
{
	return _items.at(index);
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