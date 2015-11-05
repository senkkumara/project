#ifndef FEATURE_H
#define FEATURE_H

using namespace std;

#include <memory>
#include <vector>
#include "layers.h"
#include "layer.h"

class Feature;
typedef shared_ptr<Feature> Feature_ptr;

class Feature
{
private:
	// Constructors
	Feature();

	// Member variables (private)
	Layers_ptr _layers;

	// Member functions (private)
	void init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature &f);
	friend bool operator==(Feature &f1, Feature &f2);
	friend bool operator!=(Feature &f1, Feature &f2);

public:
	// Factories
	static Feature_ptr create();

	// Getters
	Layers_ptr getLayers();
};

#endif