#ifndef SURFACE_H
#define SURFACE_H

using namespace std;

#include <memory>
#include "rises.h"
#include "layers.h"

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
	void	_init();
	void	_build(Geometry_ptr &geometry);
	void	_findInterfaces();
	void	_findInterface(Layer_ptr &layer1, Layer_ptr &layer2);
	void	_categorise();

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