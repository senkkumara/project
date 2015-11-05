using namespace std;

#include "feature.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Feature::Feature()
{
	init();
}

/**
 *	(Private) Initialises the member variables.
 */
void Feature::init()
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
 *	Get the layers the feature comprises of.
 */
Layers_ptr Feature::getLayers()
{
	return _layers;
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