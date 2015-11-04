#ifndef FEATURE_H
#define FEATURE_H

using namespace std;

#include <memory>
#include <vector>
#include "layers.h"
#include "layer.h"

class Feature
{
private:
	// Constructors
	Feature();

	// Member variables (private)
	Layers_ptr _layers;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Feature &f);
public:
	~Feature();

	// Factories
	static shared_ptr<Feature> create();

	// Getters
	Layers_ptr getLayers();
};

typedef shared_ptr<Feature> Feature_ptr;

#endif