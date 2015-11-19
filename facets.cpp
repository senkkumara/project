/**
 *	facets.cpp
 *	-----------------------------------------------------------------------
 *	See "facets.h" for a description.
 */

using namespace std;

#include "facets.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Facets::Facets()
{
	// do nothing...
}

/**
 *	Factory method using default constructor.
 */
Facets_ptr Facets::create()
{
	return Facets_ptr(new Facets());
}

/**
 *	Add a facet to the vector.
 */
void Facets::add(Facet_ptr &facet)
{
	_items.push_back(facet);
}

/**
 *	Remove a facet from the vector.
 */
void Facets::remove(Facet_ptr facet)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (facet == _items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

/**
 *	Retrieve a facet by index.
 */
Facet_ptr Facets::get(int index)
{
	return _items.at(index);
}

Facet_ptr Facets::first()
{
	return get(0);
}

Facet_ptr Facets::last()
{
	return get(size() - 1);
}

/**
 *	Return the size of the vector.
 */
int Facets::size()
{
	return _items.size();
}