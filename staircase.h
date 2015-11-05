#ifndef STAIRCASE_H
#define STAIRCASE_H

using namespace std;

#include <string>
#include <vector>
#include <memory>
#include "features.h"
#include "feature.h"
#include "layers.h"
#include "layer.h"
#include "points.h"
#include "point.h"

class Staircase;
typedef shared_ptr<Staircase> Staircase_ptr;

class Staircase
{
private:
	// Constructors
	Staircase(std::string &filename);

	// Member variables (private)
	string			_filename;
	Features_ptr	_features;
	Layers_ptr		_layers;
	Points_ptr		_points;

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm, const Staircase &s);

public:
	// Factories
	static Staircase_ptr create(string &filename);

	// Member functions (public)
	void print();

	// Getters
	Points_ptr		getPoints();
	Layers_ptr		getLayers();
	Features_ptr	getFeatures();
};

#endif