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
	Features();
	Features(Layers_ptr lyrs);
	vector<Feature_ptr> _items;
	friend std::ostream &operator<<(std::ostream &strm, const Features &fs);
public:
	~Features();
	static shared_ptr<Features> create();
	static shared_ptr<Features> create(Layers_ptr lyrs);
	vector<Feature_ptr> getItems();
	void add(Feature_ptr feat);
	void remove (Feature_ptr feat);
	Feature_ptr get(int index);
	int size();
};

typedef shared_ptr<Features> Features_ptr;

#endif