using namespace std;

#define _USE_MATH_DEFINES

#include <iostream>
#include "layers.h"
#include "layer.h"
#include "point.h"
#include "tester.h"
#include "tests.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layers::Layers()
{
	// do nothing...
}

/*
Layers::Layers(Application_ptr &app)
{
	switch (app->getGeometryType())
	{
	case GEOM_FACET:
		Layers(app->getFacets());
		break;
	case GEOM_POINT:
		Layers(app->getPoints());
		break;
	}
}
*/

/**
 *	(Private) Constructs a vector of layers from a vector
 *	containing points.
 *
 *	Do not use this directly, use the provided factory method.
 */
Layers::Layers(Points_ptr &points)
{
	// Build layers from points
	_build(points);

	// Find entry and exit edges of layers
	_findInterfaces();
	_checkInterfaces();

	// Find layer types
	_categorise();
}

Layers::Layers(Facets_ptr &facets)
{

}

/**
 *	Build the layers required to contain the points provided.
 *
 *	NB: function assumes points only ever have INCREASING Z. Will need to consider
 *	XY plane changes for applications that undulate (unlikely).
 */
void Layers::_build(Points_ptr &points)
{
	Point_ptr point;
	Layer_ptr layer;

	// Build starting layer - based on first point
	add(Layer::create(points->first()));

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
}

/**
 *	(Private) Find the entry and exit edges of each of the
 *	intermediate layers.
 */
void Layers::_findInterfaces()
{
	// Start from second layer because the function compares the exit from
	// previous layer with the entry of the current - first layer has no entry.
	for (int i = 1; i < size(); i++)
	{
		_findInterface(get(i - 1), get(i));
	}
}

/**
 *	Finds the exit interface of one layer and the entry of the subsequent layer
 *	by finding the two points on each layer with the closest proximity on the XY
 *	plane.
 *
 *	NB: this function assumes that these points are roughly directly coincident
 *	on the XY plane - one is directly above the other.
 */
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
		for (unsigned int j = 0; j < pairs.size(); j++)
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
 *	This function attempts to determine whether any of the interfaces are flipped.
 */
void Layers::_checkInterfaces()
{
	Layer_ptr layer = first();
	Edge_ptr entry;
	Edge_ptr exit = layer->exit();

	// Check the angle of the exit from the first interface is not between 90 and
	// 270 degrees
	if (exit->getZAng() > M_PI_2 && exit->getZAng() < (1.5 * M_PI))
	{
		cout << "inverting" << endl;
		exit->invert();
	}

	double tol = 45 * M_PI / 180;
	double min = M_PI - tol;		// +135
	double max = (-1 * M_PI) + tol;	// -135 (225)
	double angle;

	// Check the remaining interfaces
	for (int i = 1; i < size() - 1; i++)
	{
		layer = get(i);
		angle = layer->getIfcAngle();
		if (angle > min || angle < max)
		{
			layer->invertExit();
		}
	}
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
	closest.point2 = points->first();
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
 *	Determine and set the type of each of the layers. It will also attempt to
 *	locate and correct any interfaces that are inverted.
 */
void Layers::_categorise()
{
	get(0)->setType(LT_START);
	get(size() -1)->setType(LT_END);

	Layer_ptr layer;
	for (int i = 1; i < size() - 1; i++)
	{
		layer = get(i);
		if (Tests::isPointCountEqualTo4(layer).result)
		{
			if (Tests::isInterfaceAngleEqualTo0(layer).result)
			{
				layer->setType(LT_STRAIGHT);
			}
			else
			{
				layer->setType(LT_WINDER);
			}
		}
		else
		{
			if (Tests::isPointCountEqualTo5(layer).result)
			{
				if (Tests::isInterfaceAngleBetweenN60And60Inclusive(layer).result)
				{
					layer->setType(LT_WINDER_CORNER);
				}
				else
				{
					layer->setType(LT_LANDING_FLAT);
				}
			}
			else
			{
				layer->setType(LT_LANDING_FLAT);
			}
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
 *	Factory method using constructor with facets argument.
 */
Layers_ptr Layers::create(Facets_ptr &facets)
{
	return Layers_ptr(new Layers(facets));
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
 *	Retrieve the first layer.
 */
Layer_ptr Layers::first()
{
	return get(0);
}

/**
 *	Retrieve the last layer.
 */
Layer_ptr Layers::last()
{
	return get(size() - 1);
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
	//TODO: implement method.
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