#ifndef LAYERS_H
#define LAYERS_H

using namespace std;

#include <memory>
#include <vector>
#include "layer.h"
#include "points.h"
#include "point.h"

class Layers;
typedef shared_ptr<Layers> Layers_ptr;

class Layers
{
private:
	// Constructors
	Layers();
	Layers(Points_ptr &pnts);

	// Member variables (private)
	vector<Layer_ptr> _items;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layers &lys);

public:
	// Factories
	static Layers_ptr create();
	static Layers_ptr create(Points_ptr &points);

	// Member functions (public)
	void add(Layer_ptr &layer);
	void remove(Layer_ptr &layer);
	Layer_ptr get(int index);
	Layer_ptr findLayer(Point_ptr &point);
	int size();
	void sort();
	void trim();
	bool hasOverlaps();

	// Getters
	vector<Layer_ptr> getItems();
};

#endif