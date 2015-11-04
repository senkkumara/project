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
	Layers(Points_ptr &pnts);
	vector<Layer_ptr> _items;
	friend std::ostream &operator<<(std::ostream &strm, const Layers &lys);
public:
	~Layers();
	static shared_ptr<Layers> create(Points_ptr &pnts);
	vector<Layer_ptr> getItems();
	void add(Layer_ptr lyr);
	void remove(Layer_ptr lyr);
	Layer_ptr get(int index);
	Layer_ptr findLayer(Point_ptr pnt);
	int size();
	void sort();
	void trim();
	bool hasOverlaps();
};

typedef shared_ptr<Layers> Layers_ptr;


#endif