using namespace std;

#include "features.h"
#include <iostream>
#include "exceptions.h"
#include "feature.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Features::Features()
{
	// do nothing...
}

Features::Features(Surfaces_ptr &surfaces)
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