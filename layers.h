#ifndef LAYERS_H
#define LAYERS_H

/**
 *	facets.h
 *	-----------------------------------------------------------------------
 *	A Layers object is container for one or more Layer objects.
 */

using namespace std;

#include <memory>
#include <vector>
#include "collection.h"
#include "layer.h"

class Layers;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Layers> Layers_ptr;

/**
 *	Collection of Layers.
 */
class Layers : public Collection<Layer_ptr, Layers_ptr>
{
private:
	// Constructors
	Layers();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layers &ls);
	friend std::ostream &operator<<(std::ostream &strm,
		const Layers_ptr &ls);

public:
	// Factories
	static Layers_ptr create();

	// Methods (public)
	Layer_ptr	findLayer(Facet_ptr &facet);
	void		sort();
	bool		hasOverlaps();
};

#endif