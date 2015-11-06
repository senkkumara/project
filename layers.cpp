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

/**
 *	(Private) Find the entry and exit edges of each of the
 *	intermediate layers.
 */
void Layers::_findInterfaces()
{
	for (int i = 1; i < _items.size(); i++)
	{
		_findInterface(get(i - 1), get(i));
	}
}

void Layers::_findInterface(Layer_ptr &layer1, Layer_ptr &layer2)
{
	Points_ptr points1 = layer1->getPoints();
	Points_ptr points2 = layer2->getPoints();
	PointPair pair;
	vector<PointPair> pairs;
	PointPair smallest[2];
	Point_ptr point;
	double dist;

	// Retrieve minimum distances for each point
	for (int i = 0; i < points1->size(); i++)
	{
		point = points1->get(i);
		pair = _findClosestPoint(point, layer2);
		pairs.push_back(pair); 
	}
	
	// Extract the two points with the lowest proximity
	for (int i = 0; i < 2; i++)
	{
		// Populate holders with first element
		pair = pairs[0];
		dist = pair.dist;

		// Search map for lower values
		int k = 0;		// track position of lowest so can be removed
		for (int j = 0; j < pairs.size(); j++)
		{
			if (pairs[j].dist < dist)
			{
				k = j;
				pair = pairs[j];
				dist = pair.dist;
			}
		}

		// Remove lowest valued point from vector & add to smallest
		// array
		pairs.erase(pairs.begin() + k);
		smallest[i] = pair;
	}

	// Set interfaces
	layer1->setExit(Edge::create(smallest[0].point1, smallest[1].point1));
	layer2->setEntry(Edge::create(smallest[0].point2, smallest[1].point2));
}

/**
 *	(Private) Find the point contained by a layer that is located
 *	closest to the point provided on the xy plane.
 *
 *	This method is used in the determination of the entry and exit
 *	edges of a layer. In theory the points that comprise the exit of
 *	one layer should be located almost directly below the entry to
 *	the next.
 */
PointPair Layers::_findClosestPoint(Point_ptr &point, Layer_ptr &layer)
{
	PointPair closest;
	Points_ptr points = layer->getPoints();
	Point_ptr tmpPoint;
	double tmpDist;
	
	// Populate variables with first point
	closest.point1 = point;
	closest.point2 = points->get(0);
	closest.dist = _calculateProximity(closest.point1, closest.point2);

	// Search remaining points for a closer one
	for (int i = 1; i < points->size(); i++)
	{
		tmpPoint = points->get(i);
		tmpDist = _calculateProximity(point, tmpPoint);


		// If point is closer, update tracking variables
		if (tmpDist < closest.dist)
		{
			closest.point2 = tmpPoint;
			closest.dist = tmpDist;
		}

		if (tmpDist == 0) {
			break;
		}
	}

	return closest;
}

/**
 *	(Private) Calculates the distance between two points on the
 *	xy plane.
 */
double Layers::_calculateProximity(Point_ptr &point1, Point_ptr &point2)
{
	// uses x2 + y2 = r2
	return sqrt(pow(point2->getX() - point1->getX(), 2)
			  + pow(point2->getY() - point1->getY(), 2));
}

/**
 *	Determine and set the type of each of the layers.
 */
void Layers::_categorise()
{
	get(0)->setType(LT_START);
	get(size() -1)->setType(LT_END);

	for (int i = 1; i < size() -2; i++)
	{

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
Layer_ptr Layers::findLayer(Point_ptr &point)
{
	for (int j = _items.size() - 1; j >= 0; j--)
	{
		Layer_ptr lyr = _items.at(j);
		if (lyr->onLayer(point))
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