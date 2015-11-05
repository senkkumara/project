#ifndef LAYER_H
#define LAYER_H

using namespace std;

#include <memory>
#include <vector>
#include "points.h"
#include "point.h"
#include "edge.h"

class Layer;
typedef shared_ptr<Layer> Layer_ptr;

enum LayerType { LT_START, LT_END, LT_STRAIGHT,
	LT_WINDER, LT_FLATLANDING };

class Layer
{
private:
	// Constructors
	Layer();
	Layer(Point_ptr &ptr);

	// Member variables (private)
	double		_tol;
	double		_min;
	double		_max;
	Points_ptr	_points;
	Edge_ptr	_entry;
	Edge_ptr	_exit;
	LayerType	_type;

	// Member functions (private)
	void _init();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layer &ly);
	friend bool operator<(Layer &ly1, Layer &ly2);
	friend bool operator<=(Layer &ly1, Layer &ly2);
	friend bool operator==(Layer &ly1, Layer &ly2);
	friend bool operator!=(Layer &ly1, Layer &ly2);
	friend bool operator>=(Layer &ly1, Layer &ly2);
	friend bool operator>(Layer &ly1, Layer &ly2);
public:
	// Factories
	static Layer_ptr create();
	static Layer_ptr create(Point_ptr &pnt);

	// Member functions (public)
	void add(Point_ptr &ptr);
	void remove(Point_ptr ptr);
	bool onLayer(Point_ptr &ptr);

	// Getters
	double		getTolerance();
	double		getMin();
	double		getMax();
	Points_ptr	getPoints();
	Edge_ptr	getEntry();
	Edge_ptr	getExit();


	// Setters
	void setEntry(Edge_ptr edge);
	void setExit(Edge_ptr edge);
};

#endif