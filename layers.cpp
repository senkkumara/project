using namespace std;

#include <iostream>
#include <map>
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
	// do nothing...
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

	// Build starting layer
	add(Layer::create(points->get(0)));

	// Build remaining layers
	for (int i = 1; i < points->size(); i++)
	{
		point = points->get(i);
		layer = findLayer(point);		// Check for appropriate layer
		if (layer)
		{
			layer->add(point);			// Add to existing
		}
		else
		{
			add(Layer::create(point));	// Create new
		}
		
	}

	// Find entry and exit edges of layers
	_findInterfaces();

	// Find layer types
	_categorise();

}

Edge_ptr Layers::_findStart()
{
	return nullptr;
}

Edge_ptr Layers::_findEnd()
{
	return nullptr;
}

/**
 *	(Private) Find the entry and exit edges of each of the
 *	intermediate layers.
 */
void Layers::_findInterfaces()
{
	Layer_ptr layer;
	Points_ptr points;
	int count;
	Point_ptr pnt1;
	Point_ptr pnt2;
	Point_ptr arr[2];
	double x1;
	double x2;

	// Find start
	layer = get(0);
	points = layer->getPoints();
	count = points->size();

	// Check for invald number of points
	if (count < 2)
	{
		throw 1; // Too few points
	}
	else if (count > 2)
	{
		// Remove excess points
		_trim(layer, get(1));
	}

	pnt1 = points->get(0);
	pnt2 = points->get(1);

	x1 = pnt1->getX();
	x2 = pnt2->getX();

	if (x1 == x2)
	{
		throw 1;	// Points are coincident
	}

	arr[0] = pnt1;
	arr[1] = pnt2;

	layer->setExit(Edge::create(arr));

	// Find interfaces for all but the last layer
	for (unsigned int i = 1; i < getItems().size(); i++)
	{
		layer = get(i);

		// Find entry point
		arr[0] = _findClosestPoint(arr[0], layer);
		arr[1] = _findClosestPoint(arr[1], layer);
		layer->setEntry(Edge::create(arr));

		// Find exit point
		//..
	}

	// Find exit
	layer = get(getItems().size() - 1);
	points = layer->getPoints();
	count = points->size();

	// Check for invald number of points
	if (count < 2)
	{
		throw 1; // Too few points
	}
	else if (count > 2)
	{
		// Remove excess points
		_trim(layer, get(size() - 2));
	}

}

/**
 *	(Private) Find the point contained by a layer that is located
 *	closest to the point provided on the xy plane.
 *
 *	This method is used in the deteriination of the entry and exit
 *	edges of a layer. In theory the points that comprise the exit of
 *	one layer should be located almost directly below the entry to
 *	the next.
 */
Point_ptr Layers::_findClosestPoint(Point_ptr &point, Layer_ptr &layer)
{
	double dist;
	Point_ptr closest;
	Point_ptr tmpPoint;
	double tmpDist;
	Points_ptr points = layer->getPoints();
	
	// Populate variables with first point
	closest = points->get(0);
	dist = _calculateProximity(point, closest);

	// Search remaining points for a closer one
	for (int i = 1; i < points->size(); i++)
	{
		tmpPoint = points->get(i);
		tmpDist = _calculateProximity(point, tmpPoint);

		// If point is closer, update tracking variables
		if (tmpDist < dist)
		{
			closest = tmpPoint;
			dist = tmpDist;
		}
	}

	return closest;
}

/**
 *	(Private) Find the smallest distance between a point and the
 *	points contained by a layer.
 */
double Layers::_findClosestPointProximity(Point_ptr &point, Layer_ptr &layer)
{
	return _calculateProximity(_findClosestPoint(point, layer), point);
}

/**
 *	(Private) Calculates the distance between two points on the
 *	xy plane.
 */
double Layers::_calculateProximity(Point_ptr &p1, Point_ptr &p2)
{
	// uses x2 + y2 = r2
	return sqrt(pow(p2->getX() - p1->getX(), 2)
			  + pow(p2->getY() - p1->getY(), 2));
}

/**
 *	(Private) Removes all points from the first and last layer
 *	that do not correspond to the exit and entry to the layer
 *	respectively.
 */
void Layers::_trim(Layer_ptr &ly1, Layer_ptr &ly2)
{
	Points_ptr points1 = ly1->getPoints();
	Points_ptr points2 = ly2->getPoints();
	map<Point_ptr, double> map;
	Point_ptr point;
	double dist;

	// Retrieve minimum distances for each point
	for (int i = 0; i < points1->size(); i++)
	{
		point = points1->get(i);
		dist = _findClosestPointProximity(point, ly2);
		map.emplace(point, dist); 
	}
	
	// Remove the two points with the lowest proximity
	for (int i = 0; i < 2; i++)
	{
		// Populate holders with first element
		point = map.begin()->first;
		dist = map.begin()->second;

		// Search map for lower values
		for (auto &itr : map)
		{
			if (itr.second < dist)
			{
				point = itr.first;
				dist = itr.second;
			}
		}

		// Remove lowest valued point from map
		map.erase(map.find(point));
	}

	// Remove remaining points from the layer - leaving only
	// the two required ones
	for (auto &itr : map)
	{
		ly1->remove(itr.first);
	}
}

void Layers::_categorise()
{

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
void Layers::remove(Layer_ptr layer)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (*layer == *_items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
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

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Layers &ly)
{
	return strm;
}