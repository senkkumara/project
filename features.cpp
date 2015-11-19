using namespace std;

#include "features.h"
#include "feature.h"
#include <iostream>

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Features::Features()
{
	// do nothing...
}

Features::Features(Surface_ptr &surface)
{

}

/**
 *	(Private) Constructs a vector of features from a vector
 *	containing layers.
 *
 *	Do not use this directly, use the provided factory method.
 *//*
Features::Features(Layers_ptr &layers)
{
	// Build first two features
	add(Feature::create(layers->first()));
	add(Feature::create(layers->get(1)));

	// Build intermediate features
	Layer_ptr layer;
	FeatureType prevType;
	LayerType type;
	bool create;
	for (int i = 2; i < layers->size() -1; i++)
	{
		create = true;
		layer = layers->get(i);
		type = layer->getType();
		prevType = get(size() - 1)->getType();

		switch (type)
		{
		case LT_STRAIGHT:
			if (prevType == FT_STRAIGHT)
			{
				create = false;
			}
			break;
		case LT_WINDER:
			if (prevType == FT_WINDER)
			{
				create = false;
			}
			break;
		case LT_WINDER_CORNER:
			if (prevType == FT_WINDER)
			{
				create = false;
			}
			break;
		case LT_LANDING_FLAT:
			break;
		}

		if (create)
		{
			add(Feature::create(layer));
		}
		else
		{
			get(size() -1)->add(layer);
		}
	}

	// Build end feature
	add(Feature::create(layers->last()));
}*/

/**
 *	Factory method using default constructor.
 */
Features_ptr Features::create()
{
	return Features_ptr(new Features());
}

/**
 *	Factory method using constructor with surface argument.
 */
Features_ptr Features::create(Surface_ptr &surface)
{
	return Features_ptr(new Features(surface));
}

/**
 *	Add a feature to the vector.
 */
void Features::add(Feature_ptr &feature)
{
	_items.push_back(feature);
}

/**
 *	Remove a feature from the vector.
 */
void Features::remove(Feature_ptr &feature)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (*feature == *_items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

/**
 *	Retrieve a feature by index.
 */
Feature_ptr Features::get(int index)
{
	return _items.at(index);
}

Feature_ptr Features::first()
{
	return get(0);
}

Feature_ptr Features::last()
{
	return get(size() - 1);
}

/**
 *	Return the size of the vector.
 */
int Features::size()
{
	return _items.size();
}

/**
 *	Get the vector containing the features.
 */
vector<Feature_ptr> Features::getItems()
{
	return _items;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Features &fs)
{
	return strm;
}