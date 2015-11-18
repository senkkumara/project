/**
 *	edges.cpp
 *	-----------------------------------------------------------------------
 *	See "edges.h" for a description.
 */

using namespace std;

#include "edges.h"
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Edges::Edges()
{
	// do nothing...
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edges &es)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Operator Edges");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edges_ptr &es)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Operator Edges Pointer");
	return strm;
}

/**
 *	Factory method using default constructor.
 */
Edges_ptr Edges::create()
{
	return Edges_ptr(new Edges());
}

/**
 *	Add a edge to the vector.
 */
void Edges::add(Edge_ptr &edge)
{
	_items.push_back(edge);
}

/**
 *	Remove a edge from the vector.
 */
void Edges::remove(Edge_ptr edge)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (edge == _items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

/**
 *	Retrieve a edge by index.
 */
Edge_ptr Edges::get(int index)
{
	return _items.at(index);
}

/**
 *	Get the first edge in the vector.
 */
Edge_ptr Edges::first()
{
	return get(0);
}

/**
 *	Get the last edge in the vector.
 */
Edge_ptr Edges::last()
{
	return get(size() - 1);
}

/**
 *	Return the size of the vector.
 */
int Edges::size()
{
	return _items.size();
}