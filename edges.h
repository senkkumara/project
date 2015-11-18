#ifndef EDGES_H
#define EDGES_H

using namespace std;

#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "edge.h"

class Edges;
typedef shared_ptr<Edges> Edges_ptr;

class Edges
{
private:
	// Constructors
	Edges();
	
	// Member variables (private)
	std::vector<Edge_ptr>	_items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Edges &es);

public:
	// Factories
	static Edges_ptr create();

	// Member functions (public)
	void		add(Edge_ptr &edge);
	void		remove(Edge_ptr edge);
	Edge_ptr	get(int index);
	Edge_ptr	first();
	Edge_ptr	last();
	int			size();

	// Getters
	std::vector<Edge_ptr> getItems();
};

#endif