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
#include "collection.h"
#include "edge.h"

class Edges;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Edges> Edges_ptr;

class Edges : public Collection<Edge_ptr, Edges_ptr>
{
private:
	// Constructors
	Edges();

	// Fields (private)
	double _length;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Edges &es);
	friend std::ostream &operator<<(std::ostream &strm,
		const Edges_ptr &es);

public:
	// Factories
	static Edges_ptr create();

	// Methods (public)
	void	add(Edge_ptr &edge);		// override
	void	add(Edges_ptr &edges);		// override
	void	remove(Edge_ptr edge);		// override
	void	sort();
	double	length();
};

#endif