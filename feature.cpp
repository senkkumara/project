using namespace std;

#include "feature.h"

Feature::Feature()
{

}

Feature::~Feature()
{
	//TODO: Add destructor
}

Feature_ptr Feature::create()
{
	return Feature_ptr(new Feature());
}

Features::Features()
{

}

Features::Features(Layers_ptr lyrs)
{

}

Features::~Features()
{
	//TODO: Add destructor
}

Features_ptr Features::create()
{
	return Features_ptr(new Features());
}

Features_ptr Features::create(Layers_ptr lyrs)
{
	return Features_ptr(new Features(lyrs));
}

vector<Feature_ptr> Features::getItems()
{
	return _items;
}

/**
 *	Add a feature to the list.
 */
void Features::add(Feature_ptr feat)
{

}

/**
 *	Remove a feature from the list.
 */
void Features::remove(Feature_ptr feat)
{

}

/**
 *	Retrieve a feature by index.
 */
Feature_ptr Features::get(int index)
{
	return _items.at(index);
}

/**
 *	Return the size of the list.
 */
int Features::size()
{
	return _items.size();
}