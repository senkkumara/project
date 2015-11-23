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
	_findInterfaces();
}

void Surfaces::_init()
{
	_layers = Layers::create();
	_rises = Rises::create();
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

	cout << "Layers: " << layers->size() << endl;
	cout << "Rises: " << rises->size() << endl;
}

void Surfaces::_checkBuild()
{

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
	int j = 0;
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

}

void Surfaces::_findBoundaries()
{

}

void Surfaces::_findBoundary(Rise_ptr &rise)
{

}

void Surfaces::_findBoundary(Layer_ptr &layer)
{

}

Surfaces_ptr Surfaces::create()
{
	return Surfaces_ptr(new Surfaces());
}

Surfaces_ptr Surfaces::create(Geometry_ptr &geometry)
{
	return Surfaces_ptr(new Surfaces(geometry));
}

Layers_ptr Surfaces::getLayers()
{
	return _layers;
}

Rises_ptr Surfaces::getRises()
{
	return _rises;
}