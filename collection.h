#ifndef COLLECTION_H
#define COLLECTION_H

using namespace std;

#include <vector>

template<typename T, class V>
class Collection
{
protected:
	// Fields (protected)
	std::vector<T>	_items;

public:
	// Methods (public)
	void	add(T &item);
	void	add(V &items);
	void	remove(T item);
	T		get(int index);
	T		first();
	T		last();
	int		size();
	bool	contains(T item);
	T		get(T item);

	// Getters
	std::vector<T> getItems();
};

template<class T, class V> void Collection<T, V>::add(T &item)
{
	_items.push_back(item);
}

template<class T, class V> void Collection<T, V>::add(V &items)
{
	for (int i = 0; i < items->size(); i++)
	{
		add(items->get(i));
	}
}

template<class T, class V> void Collection<T, V>::remove(T item)
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

template<class T, class V> T Collection<T, V>::get(int index)
{
	return _items.at(index);
}

template<class T, class V> T Collection<T, V>::first()
{
	return get(0);
}

template<class T, class V> T Collection<T, V>::last()
{
	return get(size() - 1);
}

template<class T, class V> int Collection<T, V>::size()
{
	return _items.size();
}

template<class T, class V> bool Collection<T, V>::contains(T item)
{
	for (int i = 0; i < size(); i++)
	{
		if (*get(i) == *item) return true;
	}

	return false;
}

template<class T, class V> T Collection<T, V>::get(T item)
{
	for (int i = 0; i < size(); i++)
	{
		if (*get(i) == *item) return get(i);
	}

	return nullptr;
}

#endif