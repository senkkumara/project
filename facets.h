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
#include "collection.h"
#include "facet.h"

/**
 *	Collection of Facets.
 */
class Facets;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Facets> Facets_ptr;

class Facets : public Collection<Facet_ptr, Facets_ptr>
{
private:
	// Constructors
	Facets();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Facets &fs);
	friend std::ostream &operator<<(std::ostream &strm,
		const Facets_ptr &fs);

public:
	// Factories
	static Facets_ptr create();
};

#endif