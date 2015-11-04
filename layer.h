#ifndef LAYER_H
#define LAYER_H

using namespace std;

#include <memory>
#include <vector>
#include "points.h"
#include "point.h"

class Layer
{
private:
	Layer(Point_ptr);
	double _min;
	double _max;
	std::vector<Point_ptr> _pnts;
	friend std::ostream &operator<<(std::ostream &strm, const Layer &ly);
	friend bool operator<(Layer &ly1, Layer &ly2);
	friend bool operator<=(Layer &ly1, Layer &ly2);
	friend bool operator==(Layer &ly1, Layer &ly2);
	friend bool operator!=(Layer &ly1, Layer &ly2);
	friend bool operator>=(Layer &ly1, Layer &ly2);
	friend bool operator>(Layer &ly1, Layer &ly2);
public:
	static shared_ptr<Layer> create(Point_ptr pnt);
	~Layer();
	void add(Point_ptr);
	void remove(Point_ptr);
	bool onLayer(Point_ptr);
	void setMin(double);
	void setMax(double);
	double getMin();
	double getMax();
};

typedef shared_ptr<Layer> Layer_ptr;

class Layers
{
private:
	Layers(Points_ptr pnts);
	vector<Layer_ptr> _items;
	friend std::ostream &operator<<(std::ostream &strm, const Layers &lys);
public:
	~Layers();
	static shared_ptr<Layers> create(Points_ptr pnts);
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