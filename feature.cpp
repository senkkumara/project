using namespace std;

#include "feature.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature::Feature()
{
	_init();
}

Feature::Feature(Layer_ptr &layer)
{
	_init();

	switch (layer->getType())
	{
	case 1:
		_type = FT_START;
		break;
	case 2:
		_type = FT_END;
		break;
	case 3:
		_type = FT_STRAIGHT;
		break;
	case 4:
		_type = FT_WINDER;
		break;
	case 5:
		_type = FT_FLATLANDING;
		break;
	}
	
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

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Feature &f)
{
	return strm;
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