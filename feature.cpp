/**
 *	feature.cpp
 *	-----------------------------------------------------------------------
 *	See "feature.h" for a description.
 */

using namespace std;

#define _USE_MATH_DEFINES

#include "feature.h"
#include <iostream>

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature::Feature()
{
	_init();
}

/**
 *	(Private) Constructs a new Features object and adds an initial Layer
 *	object.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature::Feature(Layer_ptr &layer)
{
	_init();
	_type = _mapTypes(layer->getType());
	
	add(layer);
}

/**
 *	(Private) Initialises the member variables.
 */
void Feature::_init()
{
	_layers = Layers::create();
}

/**
 *	(Private) Maps a Layer Type into a Feature Type.
 */
FeatureType Feature::_mapTypes(LayerType type)
{
	switch (type)
	{
	case LT_START:
		return FT_START;
	case LT_END:
		return FT_END;
	case LT_STRAIGHT:
		return FT_STRAIGHT;
	case LT_WINDER:
		return FT_WINDER;
	case LT_WINDER_CORNER:
		return FT_WINDER;
	case LT_LANDING_FLAT:
		return FT_LANDING_FLAT;
	default:
		return FT_UNKNOWN;
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature &f)
{
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature_ptr &f)
{
	return strm << *f;
}

/**
 *	== operator overload.
 */
bool operator==(Feature &f1, Feature &f2)
{
	return true;
}

/**
 *	!= operator overload.
 */
bool operator!=(Feature &f1, Feature &f2)
{
	return !(f1 == f2);
}

/**
 *	== operator overload.
 */
bool operator==(Feature_ptr &f1, Feature_ptr &f2)
{
	return (*f1 == *f2);
}

/**
 *	!= operator overload.
 */
bool operator!=(Feature_ptr &f1, Feature_ptr &f2)
{
	return (*f1 != *f2);
}

/**
 *	Factory method using default constructor.
 */
Feature_ptr Feature::create()
{
	return Feature_ptr(new Feature());
}

/**
 *	Factory method using layer constructor.
 */
Feature_ptr Feature::create(Layer_ptr &layer)
{
	return Feature_ptr(new Feature(layer));
}

/**
 *	Adds a layer to the feature.
 */
void Feature::add(Layer_ptr &layer)
{
	_layers->add(layer);
}

/**
 *	Removes a layer from the feature.
 */
void Feature::remove(Layer_ptr layer)
{
	_layers->remove(layer);
}

/**
 *	Get the layers the feature comprises of.
 */
Layers_ptr Feature::getLayers()
{
	return _layers;
}

/**
 *	Get the type of the feature.
 */
FeatureType Feature::getType()
{
	return _type;
}