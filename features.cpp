using namespace std;

#include "features.h"
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

/**
 *	(Private) Constructs a vector of features from a vector
 *	containing layers.
 *
 *	Do not use this directly, use the provided factory method.
 */
Features::Features(Layers_ptr &layers)
{
	
}

/**
 *	Factory method using default constructor.
 */
Features_ptr Features::create()
{
	return Features_ptr(new Features());
}

/**
 *	Factory method using constructor with layers argument.
 */
Features_ptr Features::create(Layers_ptr &layers)
{
	return Features_ptr(new Features(layers));
}

/**
 *	Add a feature to the vector.
 */
void Features::add(Feature_ptr &feature)
{

}

/**
 *	Remove a feature from the vector.
 */
void Features::remove(Feature_ptr &feature)
{
	for (int i = 0; i < _items.size(); i++)
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
Feature_ptr Features::get(int &index)
{
	return _items.at(index);
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