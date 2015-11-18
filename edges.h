#ifndef EDGES_H
#define EDGES_H

/**
 *	edges.h
 *	-----------------------------------------------------------------------
 *	A Edges object is container for one or more Edge objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include <vector>
#include "edge.h"

class Edges;	// Pre-declare class for shared pointer typedef
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
	friend std::ostream &operator<<(std::ostream &strm,
		const Edges_ptr &es);

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