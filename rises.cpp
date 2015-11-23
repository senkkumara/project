/**
 *	rises.cpp
 *	-----------------------------------------------------------------------
 *	See "rises.h" for a description.
 */

using namespace std;

#include "rises.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Rises::Rises()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Rises &r)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Rises");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Rises_ptr &r)
{
	return strm << *r;
}

/**
 *	Factory method using default constructor.
 */
Rises_ptr Rises::create()
{
	return Rises_ptr(new Rises());
}

/**
 *	Find the rise that contains the argument facet.
 */
Rise_ptr Rises::findRise(Facet_ptr &facet)
{
	for (int j = _items.size() - 1; j >= 0; j--)
	{
		Rise_ptr rise = _items.at(j);
		if (rise->onSurface(facet))
		{
			return rise;
		}
	}

	return nullptr;
}

/**
 *	Order the layers by Z distance.
 */
void Rises::sort()
{
	Rise_ptr rise1, rise2, temp;
	for (unsigned int i = 0; i < _items.size() - 1; i++)
	{
		rise1 = get(i);
		for (unsigned int j = i + 1; j < _items.size(); j++)
		{
			rise2 = get(j);
			if (rise1->getMaxHeight() > rise2->getMaxHeight())
			{
				std::iter_swap(_items.begin() + i, _items.begin() + j);
			}
		}
	}
}