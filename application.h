#ifndef APPLICATION_H
#define APPLICATION_H

/**
 *	application.h
 *	-----------------------------------------------------------------------
 *	A Application object represents the application side of a rail design
 *	job - see "job.h". It contains geometric information about an
 *	application which can then be passed the solution side of the job -
 *	see "solution.h".
 */

using namespace std;

#include <string>
#include <vector>
#include <memory>
#include "features.h"
#include "feature.h"
#include "layers.h"
#include "layer.h"
#include "facets.h"
#include "facet.h"
#include "edges.h"
#include "edge.h"
#include "points.h"
#include "point.h"

class Application;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Application> Application_ptr;

enum GeometryType
{
	GEOM_FACET,
	GEOM_POINT
};

class Application
{
private:
	// Constructors
	Application();
	Application(std::string &filename);	// "Clean" Mode

	// Member variables (private)
	std::string		_filename;
	GeometryType	_geomType;
	Features_ptr	_features;
	Layers_ptr		_layers;
	Facets_ptr		_facets;
	Edges_ptr		_edges;
	Points_ptr		_points;
	Edges_ptr		_leftBoundary;
	Edges_ptr		_rightBoundary;

	// Member functions (private)
	void			_setGeomType(std::string &filename);

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm, const Application &s);

public:
	// Factories
	static Application_ptr create();
	static Application_ptr create(std::string &filename);

	// Member functions (public)
	void print();

	// Getters
	std::string		getFilename();
	Layers_ptr		getLayers();
	Features_ptr	getFeatures();
	Facets_ptr		getFacets();
	Edges_ptr		getEdges();
	Points_ptr		getPoints();
	Edges_ptr		left();
	Edges_ptr		right();
};

#endif