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
	// Constructors
	Layer(Point_ptr &ptr);

	// Member variables (private)
	double _min;
	double _max;
	Points_ptr _points;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layer &ly);
	friend bool operator<(Layer &ly1, Layer &ly2);
	friend bool operator<=(Layer &ly1, Layer &ly2);
	friend bool operator==(Layer &ly1, Layer &ly2);
	friend bool operator!=(Layer &ly1, Layer &ly2);
	friend bool operator>=(Layer &ly1, Layer &ly2);
	friend bool operator>(Layer &ly1, Layer &ly2);
public:
	~Layer();

	// Factories
	static shared_ptr<Layer> create(Point_ptr &pnt);

	// Member functions (public)
	void add(Point_ptr &ptr);
	void remove(Point_ptr &ptr);
	bool onLayer(Point_ptr &ptr);

	// Getters
	double getMin();
	double getMax();
	Points_ptr getPoints();

	// Setters
	void setMin(double);
	void setMax(double);
};

typedef shared_ptr<Layer> Layer_ptr;

#endif