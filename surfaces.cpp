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

	cout << "Layers: " << layers->size() << endl;
	cout << "Rises: " << rises->size() << endl;
}

void Surfaces::_findInterfaces()
{

}

void Surfaces::_findInterface(Layer_ptr &layer1, Layer_ptr &Layer2)
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