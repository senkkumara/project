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

	// Member functions (private)
	Edge_ptr	_findStart();
	Edge_ptr	_findEnd();
	void		_findInterfaces();
	Point_ptr	_findClosestPoint(Point_ptr &point, Layer_ptr &layer);
	double		_findClosestPointProximity(Point_ptr &point, Layer_ptr &layer);
	double		_calculateProximity(Point_ptr &p1, Point_ptr &p2);
	void		_trim(Layer_ptr &ly1, Layer_ptr &ly2);
	void		_categorise();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layers &lys);

public:
	// Factories
	static Layers_ptr create();
	static Layers_ptr create(Points_ptr &points);

	// Member functions (public)
	void		add(Layer_ptr &layer);
	void		remove(Layer_ptr layer);
	Layer_ptr	get(int index);
	Layer_ptr	findLayer(Point_ptr &point);
	int			size();
	void		sort();
	bool		hasOverlaps();

	// Getters
	vector<Layer_ptr> getItems();
};

#endif