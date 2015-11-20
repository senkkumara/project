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
 *	Find the layer that contains the argument part.
 */
Layer_ptr Layers::findLayer(Point_ptr &point)
{
	for (int j = _items.size() - 1; j >= 0; j--)
	{
		Layer_ptr lyr = _items.at(j);
		if (lyr->hasPoint(point))
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
	//TODO: implement method.
	throw MethodNotImplementedException("Layers::sort");
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