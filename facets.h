#ifndef FACETS_H
#define FACETS_H

/**
 *	facets.h
 *	-----------------------------------------------------------------------
 *	A Facets object is container for one or more Facet objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include <vector>
#include "facet.h"

class Facets;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Facets> Facets_ptr;

class Facets
{
private:
	// Constructors
	Facets();

	// Member variables (private)
	vector<Facet_ptr>	_items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Facets &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const Facets_ptr &fs);

public:
	// Factories
	static Facets_ptr create();

	// Member functions (public)
	void		add(Facet_ptr &facet);
	void		remove(Facet_ptr facet);
	Facet_ptr	get(int index);
	Facet_ptr	first();
	Facet_ptr	last();
	int			size();

	// Getters
	vector<Facet_ptr> getItems();
};

#endif