/**
 *	layers.cpp
 *	-----------------------------------------------------------------------
 *	See "layers.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include <iostream>
#include "layers.h"
#include "layer.h"
#include "point.h"
#include "tester.h"
#include "tests.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layers::Layers()
{
	// do nothing...
}

/**
 *	Factory method using default constructor.
 */
Layers_ptr Layers::create()
{
	return Layers_ptr(new Layers());
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Layers &ly)
{
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Layers_ptr &ly)
{
	return strm << *ly;
}

/**
 *	Find the layer that contains the argument facet.
 */
Layer_ptr Layers::findLayer(Facet_ptr &facet)
{
	for (int j = _items.size() - 1; j >= 0; j--)
	{
		Layer_ptr lyr = _items.at(j);
		if (lyr->onSurface(facet))
		{
			return lyr;
		}
	}

	return nullptr;
}

/**
 *	Order the layers by Z distance.
 */
void Layers::sort()
{
	Layer_ptr layer1, layer2, temp;
	for (unsigned int i = 0; i < _items.size() - 1; i++)
	{
		layer1 = get(i);
		for (unsigned int j = i + 1; j < _items.size(); j++)
		{
			layer2 = get(j);
			if (layer1->getMaxHeight() > layer2->getMaxHeight())
			{
				std::iter_swap(_items.begin() + i, _items.begin() + j);
			}
		}
	}
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
		if (get(i)->getMinHeight() < get(i - 1)->getMaxHeight())
		{
			return true;
		}
	}

	return false;
}