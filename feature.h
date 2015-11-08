#ifndef FEATURE_H
#define FEATURE_H

using namespace std;

#include <memory>
#include <vector>
#include "layers.h"
#include "layer.h"

class Feature;
typedef shared_ptr<Feature> Feature_ptr;

enum FeatureType
{
	FT_START,
	FT_END,
	FT_STRAIGHT,
	FT_WINDER,
	FT_WINDER_CORNER,
	FT_LANDING_FLAT,
	FT_UNKNOWN
};

class Feature
{
private:
	// Constructors
	Feature();
	Feature(Layer_ptr &layer);

	// Member variables (private)
	Layers_ptr	_layers;
	FeatureType _type;

	// Member functions (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature &f);
	friend bool operator==(Feature &f1, Feature &f2);
	friend bool operator!=(Feature &f1, Feature &f2);

public:
	// Factories
	static Feature_ptr create();
	static Feature_ptr create(Layer_ptr &layer);

	// Member functions (public)
	void add(Layer_ptr &layer);
	void remove(Layer_ptr layer);

	// Getters
	Layers_ptr		getLayers();
	FeatureType		getType();
};

#endif