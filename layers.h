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
	Layers(Points_ptr &points);

	// Member variables (private)
	vector<Layer_ptr> _items;

	// Member functions (private)
	void		_build(Points_ptr &points);
	void		_findInterfaces();
	void		_findInterface(Layer_ptr &layer1, Layer_ptr &layer2);
	void		_checkInterfaces();
	PointPair	_findClosestPoint(Point_ptr &point, Layer_ptr &layer);
	double		_calculateProximity(Point_ptr &point1, Point_ptr &point2);
	void		_trim(Layer_ptr &layer1, Layer_ptr &layer2);
	void		_categorise();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Layers &ls);

public:
	// Factories
	static Layers_ptr create();
	static Layers_ptr create(Points_ptr &points);

	// Member functions (public)
	void		add(Layer_ptr &layer);
	void		remove(Layer_ptr layer);
	Layer_ptr	get(int index);
	Layer_ptr	first();
	Layer_ptr	last();
	Layer_ptr	findLayer(Point_ptr &point);
	int			size();
	void		sort();
	bool		hasOverlaps();

	// Getters
	vector<Layer_ptr> getItems();
};

#endif