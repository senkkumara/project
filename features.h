#ifndef FEATURES_H
#define FEATURES_H

using namespace std;

#include <memory>
#include <vector>
#include "layers.h"
#include "layer.h"
#include "feature.h"

class Features
{
private:
	// Constructors
	Features();
	Features(Layers_ptr &layers);

	// Member variables (private)
	vector<Feature_ptr> _items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Features &fs);

public:
	// Factories
	static shared_ptr<Features> create();
	static shared_ptr<Features> create(Layers_ptr &layers);
	
	// Member functions (public)
	void add(Feature_ptr &feature);
	void remove (Feature_ptr &feature);
	Feature_ptr get(int &index);
	int size();

	// Getters
	vector<Feature_ptr> getItems();
};

typedef shared_ptr<Features> Features_ptr;

#endif