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

enum LayerType {
	LT_START,
	LT_END,
	LT_STRAIGHT,
	LT_WINDER,
	LT_WINDER_CORNER,
	LT_LANDING_FLAT,
	LT_UNKNOWN
};

class Layer
{
private:
	// Constructors
	Layer();
	Layer(Point_ptr &point);

	// Member variables (private)
	double		_tol;
	double		_min;
	double		_max;
	Points_ptr	_points;
	Edge_ptr	_entry;
	Edge_ptr	_exit;
	double		_ifcAngle;
	LayerType	_type;

	// Member functions (private)
	void _init();
	void _setIfcAngle();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layer &layer);
	friend bool operator<(Layer &layer1, Layer &layer2);
	friend bool operator<=(Layer &layer1, Layer &layer2);
	friend bool operator==(Layer &layer1, Layer &layer2);
	friend bool operator!=(Layer &layer1, Layer &layer2);
	friend bool operator>=(Layer &layer1, Layer &layer2);
	friend bool operator>(Layer &layer1, Layer &layer2);
public:
	// Factories
	static Layer_ptr create();
	static Layer_ptr create(Point_ptr &point);

	// Member functions (public)
	void add(Point_ptr &point);
	void remove(Point_ptr point);
	bool onLayer(Point_ptr &point);
	void invertEntry();
	void invertExit();

	// Getters
	double		getTolerance();
	double		getMin();
	double		getMax();
	Points_ptr	getPoints();
	Edge_ptr	getEntry();
	Edge_ptr	getExit();
	double		getIfcAngle();
	LayerType	getType();

	// Setters
	void setEntry(Edge_ptr edge);
	void setExit(Edge_ptr edge);
	void setType(LayerType type);
};

#endif