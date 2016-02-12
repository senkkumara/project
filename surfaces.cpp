/**
 *	surfaces.cpp
 *	-----------------------------------------------------------------------
 *	See "surfaces.h" for a description.
 */

using namespace std;

#include "surfaces.h"
#include <iostream>
#include <vector>
#include "tests.h"
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
	_boundary[0] = Edges::create();
	_boundary[1] = Edges::create();
	_nosings = Edges::create();
}

void Surfaces::_build(Geometry_ptr &geometry)
{
	Facets_ptr facets = geometry->getFacets();
	Facet_ptr facet;
	Layers_ptr layers = _layers;
	Layer_ptr layer;
	Rises_ptr rises = _rises;
	Rise_ptr rise;

	for (int i = 0; i < facets->size(); i++)
	{
		facet = facets->get(i);
		if (facet->isHorizontal())
		{
			// Facet belongs to a layer
			if (layers->size() == 0)
			{
				// No layers in collection - create new layer
				layers->add(Layer::create(facet));
			}
			else
			{
				// Layers in collection - find appropriate layer for facet
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
				// No rises in collection - create new rise
				rises->add(Rise::create(facet));
			}
			else
			{
				// Rises in collection - find appropriate rise for facet
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

	// Order surfaces by Z-distance
	layers->sort();
	rises->sort();
}

void Surfaces::_checkBuild()
{
	if (_layers->hasOverlaps())
	{
		throw GeometryBuildException();
	}
}

void Surfaces::_findInterfaces()
{
	Layers_ptr layers = _layers;
	Rises_ptr rises = _rises;

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

	// Search for rise between each layer pair
	for (int i = 0; i < layers->size() - 1; i++)
	{
		layer1 = layers->get(i);
		layer2 = layers->get(i + 1);
		layer1Z = layer1->getAvgHeight();
		layer2Z = layer2->getAvgHeight();

		// Do not reset counter - surfaces are ordered by height
		// so connecting rise cannot be lower in the stack
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

	// Check if last rise is exit for last layer
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
	Rises_ptr rises = _rises;
	Rise_ptr rise;
	Layers_ptr layers = _layers;
	Layer_ptr layer;
	Edge_ptr edge;

	// Ensure first edge is not inverted - relies on staircase being 
	// oriented such that:
	//		X: across the first step
	//		Y: along "going" of first step
	//		Z: direct of "rise" of first step
	//
	int i = 0;

	// Get first STEP - not floor - since boundaries are built in
	// lower rise + step pairs
	layer = layers->get(i);
	if (! layer->lower()->getGeometry()->size())
	{
		// First layer is the floor, not a step - want first step
		i++;
		layer = layers->get(i);
	}

	// Check step is not inverted - left should be left and right should
	// be right
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
	// Find boundary for lower rise
	_findBoundary(layer->lower());

	vector<BoundaryBuilderSnapshot_ptr> snapshots;
	Geometry_ptr geometry = layer->getGeometry();
	Edges_ptr edges = Edges::create();
	Points_ptr points = Points::create();
	Edge_ptr entry = layer->entry();
	Edge_ptr exit = layer->exit();
	Edge_ptr edge;
	Point_ptr point;
	Edges_ptr boundaries[2];
	Point_ptr current[2];

	boundaries[0] = Edges::create();
	boundaries[1] = Edges::create();

	current[0] = entry->left();
	current[1] = entry->right();

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

	// Clone points - remove entry points
	for (int i = 0; i < geometry->getPoints()->size(); i++)
	{
		point = geometry->getPoints()->get(i);
		if (*point != *current[0] && *point != *current[1])
		{
			points->add(point);
		}
		
	}
	
	// Keep trying until all of the points have been allocated -
	// assumes that points are only located on the boundary.
	while (points->size() > 0)
	{
		BoundaryBuilderSnapshot_ptr snapshot = _findNextBoundaryEdge(
			Surfaces::BoundaryBuilderSnapshot::create(), edges, points,
			entry, exit, current, boundaries);

		// Empty snapshot = failed attempt, back-steps through snapshot
		// stack trying until it finds a route.
		while (snapshot->isEmpty())
		{
			if (snapshots.size() == 0)
			{
				throw GeometryBuildException();
			}

			snapshot = _findNextBoundaryEdge(snapshots.back(), edges,
				points, entry, exit, current, boundaries);
			snapshots.pop_back();
		}

		// Add successful snapshot to stack
		snapshots.push_back(snapshot);
	}

	// Set boundaries
	layer->setLeft(boundaries[0]);
	layer->setRight(boundaries[1]);
}

Surfaces::BoundaryBuilderSnapshot_ptr Surfaces::_findNextBoundaryEdge(
		Surfaces::BoundaryBuilderSnapshot_ptr &snapshot,
		Edges_ptr &edges, Points_ptr &points,
		Edge_ptr &entry, Edge_ptr &exit,
		Point_ptr current[2], Edges_ptr boundaries[2])
{
	Point_ptr previous[2];
	Edges_ptr in[2];
	int inCount[2];
	int side = 0;
	Edge_ptr edge;
	Point_ptr removedPoint;
	Edges_ptr removedEdges = Edges::create();

	if (snapshot->isEmpty())
	{
		// Start new iteration
		in[0] = _findInboundConnections(edges, current[0]);
		in[1] = _findInboundConnections(edges, current[1]);
	}
	else
	{
		// Apply previous snapshot
		current[0] = snapshot->getPreviousLeft();
		current[1] = snapshot->getPreviousRight();

		points->add(snapshot->getRemovedPoint());
		edges->add(snapshot->getRemovedEdges());

		in[0] = snapshot->getConnectionsLeft();
		in[1] = snapshot->getConnectionsRight();
	}

	for (int i = 0; i < 2; i++)
	{
		previous[i] = current[i];
		inCount[i] = in[i]->size();
		if (exit->hasPoint(current[i])) inCount[i] = 0;
	}

	if (inCount[0] >= 1 && inCount[1] == 0)
	{
		side = 0;	// Follow left
	}
	else if (inCount[0] == 0 && inCount[1] >= 1)
	{
		side = 1;	// Follow right
	}
	else if (inCount[0] >=1 && inCount[1] >= 1)
	{
		if (in[0]->get(0)->length() < in[1]->get(0)->length())
		{
			side = 0;	// Follow left
		}
		else
		{
			side = 1;	// Follow right
		}
	}
	else
	{
		// Iteration failed, return empty snapshot to initiate back-track
		return BoundaryBuilderSnapshot::create();
	}

	// Get boundary, check for inversion and progress current point
	edge = in[side]->get(0);
	if (*current[side] != *(edge->left())) edge->invert();
	boundaries[side]->add(edge);
	current[side] = edge->right();

	in[side]->remove(edge);	// Remove route followed from in pool -
							// important back-tracking

	// Check for exit inversion
	if ((exit->hasPoint(current[0]) && *exit->left() != *current[0]) ||
		(exit->hasPoint(current[1]) && *exit->right() != *current[1]))
	{
		exit->invert();
	}

	// Remove point from pool - must be *before* edges
	removedPoint = current[side];
	points->remove(removedPoint);

	// Remove edges from "edges" collection where neither end
	// point is in the "points" collection
	for (int i = edges->size() - 1; i > -1; i--)
	{
		edge = edges->get(i);
		if (edge->hasPoint(removedPoint)
			&& (!points->contains(edge->left()))
			&& (!points->contains(edge->right())))
		{
			removedEdges->add(edge);
			edges->remove(edge);
		}
	}

	// Return successful snapshot!
	return BoundaryBuilderSnapshot::create(previous[0], previous[1],
		removedPoint, removedEdges, in[0], in[1]);
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
	edge = _findShortestInboundConnection(rise, entry->left());
	if (edge->left()->getZ() > edge->right()->getZ()) edge->invert();
	boundary->add(edge);
	rise->setLeft(boundary);

	// Right boundary
	boundary = Edges::create();
	edge = _findShortestInboundConnection(rise, entry->right());
	if (edge->left()->getZ() > edge->right()->getZ()) edge->invert();
	boundary->add(edge);
	rise->setRight(boundary);

	// Check upper boundary
	point = rise->left()->get(0)->right();
	if (! exit->hasPoint(point))
	{
		// Upper boundary points do not match up!
		throw GeometryBuildException();
	}

	if (*point != *exit->left())
	{
		// Upper boundary is inverted
		exit->invert();
	}
}

/**
 *	(Private) Returns on the shortest edge going into a point.
 */
Edge_ptr Surfaces::_findShortestInboundConnection(Rise_ptr &rise,
												  Point_ptr &point)
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

/**
 *	Finds all of the inbound edges to a point in a pool of edges.
 */
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

/**
 *	
 */
void Surfaces::_collectBoundaries()
{
	Layers_ptr layers = _layers;
	Layer_ptr layer;

	// First layer
	layer = layers->first();
	int i = 0;
	if (layer->lower()->getGeometry()->size() == 0)
	{
		// Layer is the floor - not a step
		_boundary[0]->add(layer->left());
		_boundary[1]->add(layer->right());
		i++;
	}

	// Remaining layers
	for (; i < layers->size(); i++)
	{
		layer = layers->get(i);

		_boundary[0]->add(layer->lower()->left());
		_boundary[1]->add(layer->lower()->right());
		_boundary[0]->add(layer->left());
		_boundary[1]->add(layer->right());
	}

	// Add boundary for rise from last layer if it exists
	if (layer->upper()->getGeometry()->size() > 0)
	{
		_boundary[0]->add(layer->upper()->left());
		_boundary[1]->add(layer->upper()->right());
	}
}

/**
 *
 */
void Surfaces::_collectNosings()
{
	int count = _rises->size();
	if (! count) return;

	for (unsigned int i = 0; i < count; i++)
	{
		_nosings->add(_rises->get(i)->exit());
	}
}

/**
 *	
 */
void Surfaces::_categorise()
{
	Layer_ptr layer;
	int i = 0;
	int end = _layers->size();

	layer = _layers->get(i);
	if (Tests::Layer::isStart(layer).result)
	{
		layer->setType(Layer::LAYER_TYPE_START);
		i++;
	}
	layer = _layers->get(end - 1);
	if (Tests::Layer::isEnd(layer).result)
	{
		layer->setType(Layer::LAYER_TYPE_END);
		end--;
	}

	for (; i < end; i++)
	{
		layer = _layers->get(i);
		if (Tests::Layer::isStraightStandard(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_STRAIGHT);
			layer->setSubType(Layer::LAYER_SUB_TYPE_STANDARD);
			continue;
		}
		
		if (Tests::Layer::isWinderStandard(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_WINDER);
			layer->setSubType(Layer::LAYER_SUB_TYPE_STANDARD);
			continue;
		}
		
		if (Tests::Layer::isWinderCornerOuter(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_WINDER);
			layer->setSubType(Layer::LAYER_SUB_TYPE_CORNER_OUTER);
			continue;
		}

		if (Tests::Layer::isWinderCornerInner(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_WINDER);
			layer->setSubType(Layer::LAYER_SUB_TYPE_CORNER_INNER);
			continue;
		}

		if (Tests::Layer::isLanding90(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_LANDING);
			layer->setSubType(Layer::LAYER_SUB_TYPE_90);
			continue;
		}

		if (Tests::Layer::isLanding180(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_LANDING);
			layer->setSubType(Layer::LAYER_SUB_TYPE_180);
			continue;
		}

		if (Tests::Layer::isStraightExtended(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_STRAIGHT);
			layer->setSubType(Layer::LAYER_SUB_TYPE_EXTENDED);
			continue;
		}

		if (Tests::Layer::isWinderNarrow(layer).result)
		{
			layer->setType(Layer::LAYER_TYPE_WINDER);
			layer->setSubType(Layer::LAYER_SUB_TYPE_NARROW);
			continue;
		}
	}

	cout << "Layers: " << endl;
	for (int i = 0; i < _layers->size(); i++)
	{
		cout << "Type: " << _layers->get(i)->getType() << " Sub Type: " << _layers->get(i)->getSubType() << endl;
	}
}

/**
 *	
 */
Surfaces_ptr Surfaces::create()
{
	return Surfaces_ptr(new Surfaces());
}

/**
 *	
 */
Surfaces_ptr Surfaces::create(Geometry_ptr &geometry)
{
	return Surfaces_ptr(new Surfaces(geometry));
}

/**
 *	
 */
Edges_ptr Surfaces::left()
{
	return _boundary[0];
}

/**
 *	
 */
Edges_ptr Surfaces::right()
{
	return _boundary[1];
}

/**
 *
 */
Layers_ptr Surfaces::getLayers()
{
	return _layers;
}

/**
 *
 */
Rises_ptr Surfaces::getRises()
{
	return _rises;
}

/**
 *
 */
Edges_ptr Surfaces::getNosings()
{
	return _nosings;
}

/**
 *	
 */
Surfaces::BoundaryBuilderSnapshot::BoundaryBuilderSnapshot()
{
	_empty = true;
}

/**
 *	
 */
Surfaces::BoundaryBuilderSnapshot::BoundaryBuilderSnapshot(
	Point_ptr &left, Point_ptr &right,
	Point_ptr &removedPoint, Edges_ptr &removedEdges,
	Edges_ptr &connectionsLeft, Edges_ptr &connectionsRight)
{
	_empty = false;
	_previous[0] = left;
	_previous[1] = right;
	_removedPoint = removedPoint;
	_removedEdges = removedEdges;
	_connections[0] = connectionsLeft;
	_connections[1] = connectionsRight;
}

/**
 *	
 */
Surfaces::BoundaryBuilderSnapshot_ptr 
	Surfaces::BoundaryBuilderSnapshot::create()
{
	return BoundaryBuilderSnapshot_ptr(new
		BoundaryBuilderSnapshot());
}

/**
 *	
 */
Surfaces::BoundaryBuilderSnapshot_ptr 
	Surfaces::BoundaryBuilderSnapshot::create(
			Point_ptr &left, Point_ptr &right,
			Point_ptr &removedPoint, Edges_ptr &removedEdges,
			Edges_ptr &connectionsLeft, Edges_ptr &connectionsRight)
{
	return BoundaryBuilderSnapshot_ptr(new
		BoundaryBuilderSnapshot(left, right, removedPoint, removedEdges,
		connectionsLeft, connectionsRight));
}

/**
 *	
 */
bool Surfaces::BoundaryBuilderSnapshot::isEmpty()
{
	return _empty;
}

/**
 *	
 */
Point_ptr* Surfaces::BoundaryBuilderSnapshot::getPrevious()
{
	return _previous;
}

/**
 *	
 */
Point_ptr Surfaces::BoundaryBuilderSnapshot::getPreviousLeft()
{
	return _previous[0];
}

/**
 *	
 */
Point_ptr Surfaces::BoundaryBuilderSnapshot::getPreviousRight()
{
	return _previous[1];
}

/**
 *	
 */
Point_ptr Surfaces::BoundaryBuilderSnapshot::getRemovedPoint()
{
	return _removedPoint;
}

/**
 *	
 */
Edges_ptr Surfaces::BoundaryBuilderSnapshot::getRemovedEdges()
{
	return _removedEdges;
}

/**
 *	
 */
Edges_ptr* Surfaces::BoundaryBuilderSnapshot::getConnections()
{
	return _connections;
}

/**
 *	
 */
Edges_ptr Surfaces::BoundaryBuilderSnapshot::getConnectionsLeft()
{
	return _connections[0];
}

/**
 *	
 */
Edges_ptr Surfaces::BoundaryBuilderSnapshot::getConnectionsRight()
{
	return _connections[1];
}