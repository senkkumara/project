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

enum FileType
{
	DXF,
	STL
};

class Staircase
{
private:
	// Constructors
	Staircase();						// "Iterate" Mode
	Staircase(std::string &filename);	// "Clean" Mode

	// Member variables (private)
	string			_filename;
	Features_ptr	_features;
	Layers_ptr		_layers;
	Points_ptr		_points;
	//Facets_ptr	_facets;
	//Edges_ptr		_leftBoundary;
	//Edges_ptr		_rightBoundary;

	// Member functions (private)
	void _extractGeometry(string &filename);
	void _extractGeometryFromSTL(string &filename);
	void _extractGeometryFromDXF(string &filename);
	void _extractGeometryFromFile();

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm, const Staircase &s);

public:
	// Factories
	static Staircase_ptr create();
	static Staircase_ptr create(string &filename);

	// Member functions (public)
	void print();

	// Getters
	string			getFilename();
	Points_ptr		getPoints();
	Layers_ptr		getLayers();
	Features_ptr	getFeatures();
	//Facets_ptr	getFacets();
	//Edges_ptr		left();
	//Edges_ptr		right();
};

#endif