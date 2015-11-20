#ifndef LAYERS_H
#define LAYERS_H

using namespace std;

#include <memory>
#include <vector>
#include "collection.h"
#include "layer.h"

class Layers;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Layers> Layers_ptr;

class Layers : public Collection<Layer_ptr>
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
	Layer_ptr	findLayer(Point_ptr &point);
	void		sort();
	bool		hasOverlaps();
};

#endif