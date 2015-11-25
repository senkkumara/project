#ifndef LAYER_H
#define LAYER_H

/**
 *	layer.h
 *	-----------------------------------------------------------------------
 *	A layer object contains facets, edges and points that are at a given 
 *	z-distance. Generally speaking the capture the geometry of individual
 *	steps or landings.
 */

using namespace std;

#include <memory>
#include "surface.h"
#include "rise.h"

class Layer;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Layer> Layer_ptr;

enum LayerType {
	LT_START,
	LT_END,
	LT_STRAIGHT,
	LT_WINDER,
	LT_WINDER_CORNER,
	LT_LANDING_FLAT_90,
	LT_LANDING_FLAT_180,
	LT_LANDING_FLAT_UNKNOWN,
	LT_UNKNOWN
};

class Layer : public Surface
{
private:
	// Constructors
	Layer();
	Layer(Facet_ptr &facet);

	// Fields (private)
	LayerType	_type;
	Rise_ptr	_lower;
	Rise_ptr	_upper;

	// Methods (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Layer &layer);

	friend std::ostream &operator<<(std::ostream &strm,
		const Layer_ptr &layer);

	friend bool operator<(Layer &layer1, Layer &layer2);
	friend bool operator<=(Layer &layer1, Layer &layer2);
	friend bool operator==(Layer &layer1, Layer &layer2);
	friend bool operator!=(Layer &layer1, Layer &layer2);
	friend bool operator>=(Layer &layer1, Layer &layer2);
	friend bool operator>(Layer &layer1, Layer &layer2);

public:
	// Factories
	static Layer_ptr create();
	static Layer_ptr create(Facet_ptr &facet);

	// Methods (private)
	Rise_ptr		lower();
	Rise_ptr		upper();

	// Getters
	LayerType		getType();

	// Setters
	void setType(LayerType type);
	void setLower(Rise_ptr &rise);
	void setUpper(Rise_ptr &rise);
};

#endif