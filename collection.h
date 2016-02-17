#ifndef COLLECTION_H
#define COLLECTION_H

/**
 *	collection.h
 *	---------------------------------------------------------------------------
 *	Defines a template for a collection container.
 */

using namespace std;

#include <vector>
#include "exceptions.h"
#include <iostream>

/**
 *	"C" is the container type - e.g. "Points_ptr" (required for clone)
 *	"V" is the value type - e.g. "Point_ptr"
 */
template<typename V, class C>
class Collection
{
protected:
	// Fields (protected)
	std::vector<V>	_items;

public:
	// Methods (public)
	void			add(V &item);
	void			add(C &items);
	void			insert(V &item, int index);
	void			remove(V item);
	V				get(int index);
	V				first();
	V				last();
	int				size();
	bool			contains(V item);
	V				get(V item);
	std::vector<V>	getItems();
};

template<class V, class C> void Collection<V, C>::add(V &item)
{
	_items.push_back(item);
}

template<class V, class C> void Collection<V, C>::add(C &items)
{
	for (int i = 0; i < items->size(); i++)
	{
		add(items->get(i));
	}
}

template<class V, class C> void Collection<V, C>::insert(V &item, int index)
{
	_items.insert(_items.begin() + index, item);
}

template<class V, class C> void Collection<V, C>::remove(V item)
{
	for (unsigned int i = 0; i < _items.size(); i++)
	{
		if (item == _items.at(i))
		{
			_items.erase(_items.begin() + i);
			return;
		}
	}
}

template<class V, class C> V Collection<V, C>::get(int index)
{
	return _items.at(index);
}

template<class V, class C> V Collection<V, C>::first()
{
	return get(0);
}

template<class V, class C> V Collection<V, C>::last()
{
	return get(size() - 1);
}

template<class V, class C> int Collection<V, C>::size()
{
	return _items.size();
}

template<class V, class C> bool Collection<V, C>::contains(V item)
{
	for (int i = 0; i < size(); i++)
	{
		if (*get(i) == *item) return true;
	}

	return false;
}

template<class V, class C> V Collection<V, C>::get(V item)
{
	for (int i = 0; i < size(); i++)
	{
		if (*get(i) == *item) return get(i);
	}

	return nullptr;
}

#endif