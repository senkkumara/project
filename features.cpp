using namespace std;

#include "features.h"
#include <iostream>
#include "exceptions.h"
#include "feature.h"
#include "surfaces.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Features::Features()
{
	// do nothing...
}

/**
 *	(Private) Constructs a vector of features from a vector
 *	containing layers.
 *
 *	Do not use this directly, use the provided factory method.
 */
Features::Features(Surfaces_ptr &surfaces)
{
	Layers_ptr layers = surfaces->getLayers();

	// Build first feature
	add(Feature::create(layers->first()));

	// Build intermediate features
	Layer_ptr layer;
	FeatureType prevType;
	LayerType type;
	bool create;
	for (int i = 2; i < layers->size(); i++)
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
		case LT_LANDING_FLAT_UNKNOWN:
		case LT_LANDING_FLAT_180:
		case LT_LANDING_FLAT_90:
			break;
		}
		if (create)
		{
			cout << "Creating new..." <<  layer->getType() << endl;
			add(Feature::create(layer));
		}
		else
		{
			cout << "Adding to exiting..." << endl;
			get(size() - 1)->add(layer);
		}
	}

	cout << "Features: " << endl;
	for (int i = 0; i < size(); i++)
	{
		cout << get(i)->getType() << endl;
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Features &fs)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Features");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Features_ptr &fs)
{
	return strm << *fs;
}

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
Features_ptr Features::create(Surfaces_ptr &surfaces)
{
	return Features_ptr(new Features(surfaces));
}