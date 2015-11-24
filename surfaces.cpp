/**
 *	surfaces.cpp
 *	-----------------------------------------------------------------------
 *	See "surfaces.h" for a description.
 */

using namespace std;

#include "surfaces.h"
#include <iostream>
#include "exceptions.h"

Surfaces::Surfaces()
{
	_init();
}

Surfaces::Surfaces(Geometry_ptr &geometry)
{
	_init();
	_build(geometry);
	_checkBuild();
	_findInterfaces();
	_checkInterfaces();
	_findBoundaries();
	_checkBoundaries();
	_collectBoundaries();
	_categorise();
}

void Surfaces::_init()
{
	_layers = Layers::create();
	_rises = Rises::create();
	_left = Edges::create();
	_right = Edges::create();
}

void Surfaces::_build(Geometry_ptr &geometry)
{
	Facets_ptr facets = geometry->getFacets();
	Facet_ptr facet;
	Layers_ptr layers = getLayers();
	Layer_ptr layer;
	Rises_ptr rises = getRises();
	Rise_ptr rise;

	for (int i = 0; i < facets->size(); i++)
	{
		facet = facets->get(i);
		if (! facet->isVertical())
		{
			// Facet belongs to a layer
			if (layers->size() == 0)
			{
				layers->add(Layer::create(facet));
			}
			else
			{
				layer = layers->findLayer(facet);
				if (layer)
				{
					layer->add(facet);
				}
				else
				{
					layers->add(Layer::create(facet));
				}
			}
		}
		else
		{
			// Facet belongs to a riser
			if (rises->size() == 0)
			{
				rises->add(Rise::create(facet));
			}
			else
			{
				rise = rises->findRise(facet);
				if (rise)
				{
					rise->add(facet);
				}
				else
				{
					rises->add(Rise::create(facet));
				}
			}
		}
	}

	layers->sort();
	rises->sort();
}

void Surfaces::_checkBuild()
{
	if (getLayers()->hasOverlaps())
	{
		throw GeometryBuildException();
	}
}

void Surfaces::_findInterfaces()
{
	Layers_ptr layers = getLayers();
	Rises_ptr rises = getRises();

	// Rises
	for (int i = 0; i < rises->size(); i++)
	{
		_findInterface(rises->get(i));
	}
	
	// Layers
	int j = 0;	// Record position in rises collection -
				// reduce number of iterations

	Layer_ptr layer1, layer2;
	Rise_ptr rise;
	double layer1Z, layer2Z, riseZ;

	layer1 = layers->first();
	rise = rises->first();

	if (rise->getAvgHeight() < layer1->getAvgHeight())
	{
		layer1->setLower(rise);
		layer1->setEntry(rise->exit());
	}


	for (int i = 0; i < layers->size() - 1; i++)
	{
		layer1 = layers->get(i);
		layer2 = layers->get(i + 1);
		layer1Z = layer1->getAvgHeight();
		layer2Z = layer2->getAvgHeight();

		for (; j < rises->size(); j++)
		{
			rise = rises->get(j);
			riseZ = rise->getAvgHeight();
			if (layer1Z < riseZ && riseZ < layer2Z)
			{
				layer1->setUpper(rise);
				layer2->setLower(rise);

				layer1->setExit(rise->entry());
				layer2->setEntry(rise->exit());
				break;
			}
		}
	}

	layer1 = layers->last();
	rise = rises->last();

	if (rise->getAvgHeight() > layer1->getAvgHeight())
	{
		layer1->setUpper(rise);
		layer1->setExit(rise->entry());
	}

}

void Surfaces::_findInterface(Rise_ptr &rise)
{
	Edges_ptr edges = rise->getGeometry()->getEdges();
	Edge_ptr max = edges->get(0);
	Edge_ptr min = max;
	Edge_ptr edge;
	double maxZ = max->getAvgZ();
	double minZ = maxZ;
	double edgeAvgZ;

	// Find edges with highest and lowest Average Z
	if (edges->size() > 1) {
		for (int i = 1; i < edges->size(); i++)
		{
			edge = edges->get(i);
			edgeAvgZ = edge->getAvgZ();

			if (edgeAvgZ < minZ)
			{
				min = edge;
				minZ = edgeAvgZ;
				continue;
			}

			if (edgeAvgZ > maxZ)
			{
				max = edge;
				maxZ = edgeAvgZ;
				continue;
			}
		}
	}

	rise->setEntry(min);
	rise->setExit(max);
}

void Surfaces::_checkInterfaces()
{
	// do nothing...
}

void Surfaces::_findBoundaries()
{
	Rises_ptr rises = getRises();
	Rise_ptr rise;
	Layers_ptr layers = getLayers();
	Layer_ptr layer;
	Edge_ptr edge;

	// Ensure first edge is not inverted
	int i = 0;
	layer = layers->get(i);
	if (! layer->lower()->getGeometry()->size())
	{
		i++;
		layer = layers->get(i);
	}

	edge = layer->lower()->entry();
	if (edge->left()->getX() > edge->right()->getX())
	{
		edge->invert();
	}

	// Find layer boundaries
	int end = layers->size();
	if (! layers->last()->upper()->getGeometry()->size()) end--;
	for (; i < end; i++)
	{
		layer = layers->get(i);
		_findBoundary(layer);
	}
	
	// Find topmost rise boundary if final surface is a rise -
	// previous loop is backwards looking, only creating boundaries
	// for lower rise
	if (layer->upper()->getGeometry()->size() != 0)
	{
		_findBoundary(layer->upper());
	}
}

void Surfaces::_findBoundary(Layer_ptr &layer)
{
	_findBoundary(layer->lower());

	Geometry_ptr geometry = layer->getGeometry();
	Edges_ptr edges = Edges::create();
	Edges_ptr boundary1 = Edges::create();
	Edges_ptr boundary2 = Edges::create();
	Edges_ptr inbound1, inbound2;
	Edge_ptr entry = layer->entry();
	Edge_ptr exit = layer->exit();
	Edge_ptr edge;
	Points_ptr points = Points::create();
	Point_ptr left = entry->left();
	Point_ptr right = entry->right();
	Point_ptr point;
	int inCount1, inCount2;

	// Clone edges - remove entry and exit
	for (int i = 0; i < geometry->getEdges()->size(); i++)
	{
		edge = geometry->getEdges()->get(i);

		// do not add entry and exit edges
		if (*edge != *entry && *edge != *exit)
		{
			edges->add(edge);
		}
	}

	// Clone points - remove
	for (int i = 0; i < geometry->getPoints()->size(); i++)
	{
		point = geometry->getPoints()->get(i);
		if (*point != *left && *point != *right)
		{
			points->add(point);
		}
		
	}
	
	while (points->size() > 0)
	{
		inbound1 = _findInboundConnections(edges, left);
		inbound2 = _findInboundConnections(edges, right);

		inCount1 = inbound1->size();
		inCount2 = inbound2->size();

		if (exit->hasPoint(left)) inCount1 = 0;
		if (exit->hasPoint(right)) inCount2 = 0;

		if (inCount1 >= 1 && inCount2 == 0)
		{
			edge = inbound1->get(0);
			if (*left != *(edge->left())) edge->invert();
			boundary1->add(edge);
			left = edge->right();
			point = left;
		}
		else if (inCount1 == 0 && inCount2 >= 1)
		{
			edge = inbound2->get(0);
			if (*right != *(edge->left())) edge->invert();
			boundary2->add(edge);
			right = edge->right();
			point = right;
		}
		else if (inCount1 >= 1 && inCount2 >= 1)
		{
			if (inbound1->get(0)->length() < inbound2->get(0)->length())
			{
				edge = inbound1->get(0);
				if (*left != *(edge->left())) edge->invert();
				boundary1->add(edge);
				left = edge->right();
				point = left;
			}
			else
			{
				edge = inbound2->get(0);
				if (*right != *(edge->left())) edge->invert();
				boundary2->add(edge);
				right = edge->right();
				point = right;
			}
		}
		else
		{
			// TODO: build in a "back step"
			throw GeometryBuildException();
		}

		if ((exit->hasPoint(left) && *exit->left() != *left) ||
			(exit->hasPoint(right) && *exit->right() != *right))
		{
			exit->invert();
		}

		// Remove point from pool - must be *before* edges
		points->remove(point);

		// Remove edges from "edges" collection where neither end
		// point is in the "points" collection
		for (int i = edges->size() - 1; i > -1; i--)
		{
			edge = edges->get(i);
			if (edge->hasPoint(point)
				&& (!points->contains(edge->left()))
				&& (!points->contains(edge->right())))
			{
				edges->remove(edge);
			}
		}
	}

	// Set boundaries
	layer->setLeft(boundary1);
	layer->setRight(boundary2);
}

void Surfaces::_findBoundary(Rise_ptr &rise)
{
	Edges_ptr edges = rise->getGeometry()->getEdges();
	Edge_ptr edge;
	Edges_ptr boundary;
	Edge_ptr entry = rise->entry();
	Edge_ptr exit = rise->exit();
	Point_ptr point;
	
	// Left boundary
	boundary = Edges::create();
	edge = _findShortestConnected(rise, entry->left());
	if (edge->left()->getZ() > edge->right()->getZ()) edge->invert();
	boundary->add(edge);
	rise->setLeft(boundary);

	// Right boundary
	boundary = Edges::create();
	edge = _findShortestConnected(rise, entry->right());
	if (edge->left()->getZ() > edge->right()->getZ()) edge->invert();
	boundary->add(edge);
	rise->setRight(boundary);

	// Check upper boundary
	point = rise->left()->get(0)->right();
	if (! exit->hasPoint(point))
	{
		throw GeometryBuildException();
	}

	if (*point != *exit->left())
	{
		exit->invert();
	}
}

Edge_ptr Surfaces::_findShortestConnected(Rise_ptr &rise, Point_ptr &point)
{
	Edges_ptr edges = rise->getGeometry()->getEdges();
	Edge_ptr entry = rise->entry();
	Edge_ptr exit = rise->exit();
	Edge_ptr edge;
	Edge_ptr tempEdge;

	for (int i = 0; i < edges->size(); i++)
	{
		tempEdge = edges->get(i);
		if (tempEdge == entry || tempEdge == exit)
		{
			continue;
		}

		if (tempEdge->hasPoint(point))
		{
			if (edge)
			{
				if (edge->length() > tempEdge->length())
				{
					edge = tempEdge;
				}
			}
			else
			{
				edge = tempEdge;
			}
		}
	}

	return edge;
}

Edges_ptr Surfaces::_findInboundConnections(Edges_ptr &edges,
											Point_ptr &point)
{
	Edges_ptr connections = Edges::create();
	Edge_ptr edge;
	
	for (int i = 0; i < edges->size(); i++)
	{
		edge = edges->get(i);
		if (edge->hasPoint(point)) connections->add(edge);
	}

	connections->sort();
	return connections;
}

void Surfaces::_checkBoundaries()
{
	// do nothing...
}

void Surfaces::_collectBoundaries()
{
	Layers_ptr layers = getLayers();
	Layer_ptr layer;

	// First layer
	layer = layers->first();
	int i = 0;
	if (layer->lower()->getGeometry()->size() == 0)
	{
		cout << "Layer 1: ";
		cout << layer->left()->size() << ", " << layer->right()->size() << endl;
		_left->add(layer->left());
		_right->add(layer->right());
		i++;
	}

	
	for (; i < layers->size(); i++)
	{
		layer = layers->get(i);

		cout << "Rise " << (i + 1) << ": ";
		cout << layer->lower()->left()->size() << ", " << layer->lower()->right()->size() << endl;
		cout << "Layer " << (i + 1) << ": ";
		cout << layer->left()->size() << ", " << layer->right()->size() << endl;
		_left->add(layer->lower()->left());
		_right->add(layer->lower()->right());
		_left->add(layer->left());
		_right->add(layer->right());
	}

	// Add boundary for rise from last layer if it exists
	if (layer->upper()->getGeometry()->size() > 0)
	{
		cout << "Rise " << _rises->size() << ": ";
		cout << layer->upper()->left()->size() << ", " << layer->upper()->right()->size() << endl;
		_left->add(layer->upper()->left());
		_right->add(layer->upper()->right());
	}
}

void Surfaces::_categorise()
{
	// do nothing...
}

Surfaces_ptr Surfaces::create()
{
	return Surfaces_ptr(new Surfaces());
}

Surfaces_ptr Surfaces::create(Geometry_ptr &geometry)
{
	return Surfaces_ptr(new Surfaces(geometry));
}

Edges_ptr Surfaces::left()
{
	return _left;
}

Edges_ptr Surfaces::right()
{
	return _right;
}

Layers_ptr Surfaces::getLayers()
{
	return _layers;
}

Rises_ptr Surfaces::getRises()
{
	return _rises;
}