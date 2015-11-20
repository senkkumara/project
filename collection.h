#ifndef COLLECTION_H
#define COLLECTION_H

using namespace std;

#include <vector>

template<typename T>
class Collection
{
protected:
	// Fields (protected)
	std::vector<T>	_items;

public:
	// Methods (public)
	void	add(T &item);
	void	remove(T item);
	T		get(int index);
	T		first();
	T		last();
	int		size();
	bool	contains(T item);

	// Getters
	std::vector<T> getItems();
};

template<class T> void Collection<T>::add(T &item)
{
	_items.push_back(item);
}

template<class T> void Collection<T>::remove(T item)
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

template<class T> T Collection<T>::get(int index)
{
	return _items.at(index);
}

template<class T> T Collection<T>::first()
{
	return get(0);
}

template<class T> T Collection<T>::last()
{
	return get(size() - 1);
}

template<class T> int Collection<T>::size()
{
	return _items.size();
}

template<class T> bool Collection<T>::contains(T item)
{
	for (int i = 0; i < size(); i++)
	{
		if (get(i) == item) return true;
	}

	return false;
}

#endif