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
	throw MethodNotImplementedException("<< Edges");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Edges_ptr &es)
{
	return strm << *es;
}

/**
 *	Factory method using default constructor.
 */
Edges_ptr Edges::create()
{
	return Edges_ptr(new Edges());
}

/**
 *	Order the edges by length using the "bubble sort" method.
 */
void Edges::sort()
{
	if (size() < 2) return;

	Edge_ptr edge1, edge2, temp;
	for (int i = 0; i < size() - 1; i++)
	{
		edge1 = get(i);
		for (int j = i + 1; j < size(); j++)
		{
			edge2 = get(j);
			if (edge1->length() > edge2->length())
			{
				std::iter_swap(_items.begin() + i, _items.begin() + j);
			}
		}
	}
}