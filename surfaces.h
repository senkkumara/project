#ifndef SURFACES_H
#define SURFACES_H

using namespace std;

#include <memory>
#include "rises.h"
#include "rise.h"
#include "layers.h"
#include "layer.h"

class Surfaces;
typedef shared_ptr<Surfaces> Surfaces_ptr;

class Surfaces
{
private:
	// Constructors
	Surfaces();
	Surfaces(Geometry_ptr &geometry);

	// Fields (private)
	Layers_ptr	_layers;
	Rises_ptr	_rises;

	// Methods (private)
	void		_init();
	void		_build(Geometry_ptr &geometry);
	void		_checkBuild();
	void		_findInterfaces();
	void		_findInterface(Rise_ptr &rise);
	void		_checkInterfaces();
	void		_findBoundaries();
	void		_findBoundary(Layer_ptr &layer);
	void		_findBoundary(Rise_ptr &rise);
	Edge_ptr	_findShortestConnected(Rise_ptr &rise, Point_ptr &point);
	Edges_ptr	_findInboundConnections(Edges_ptr &edges, Point_ptr &point);
	void		_checkBoundaries();
	void		_categorise();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Surfaces &s);
	friend std::ostream &operator<<(std::ostream &strm,
		const Surfaces_ptr &s);

public:
	// Factories
	static Surfaces_ptr create();
	static Surfaces_ptr create(Geometry_ptr &geometry);

	// Getters
	Layers_ptr	getLayers();
	Rises_ptr	getRises();
};

#endif