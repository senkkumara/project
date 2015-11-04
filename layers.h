#ifndef LAYERS_H
#define LAYERS_H

using namespace std;

#include <memory>
#include <vector>
#include "layer.h"
#include "points.h"
#include "point.h"

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
	static shared_ptr<Layers> create();
	static shared_ptr<Layers> create(Points_ptr &points);

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

typedef shared_ptr<Layers> Layers_ptr;


#endif