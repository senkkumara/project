#ifndef FACETS_H
#define FACETS_H

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
	Facets(std::string &filename);

	// Member variables (private)
	vector<Facet_ptr>	_items;
	std::string			_filename;
	void _extractFromSTL(std::string &filename);
	void _extractFromDXF(std::string &filename);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Facets &fs);

public:
	// Factories
	static Facets_ptr create();
	static Facets_ptr create(std::string &filename);

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