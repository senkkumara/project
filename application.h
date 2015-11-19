#ifndef APPLICATION_H
#define APPLICATION_H

/**
 *	application.h
 *	-----------------------------------------------------------------------
 *	An Application object represents the application side of a rail design
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
#include "geometry.h"

class Application;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Application> Application_ptr;

class Application
{
private:
	// Constructors
	Application();
	Application(std::string &filename);	// "Clean" Mode

	// Member variables (private)
	std::string		_filename;
	Features_ptr	_features;
	Layers_ptr		_layers;
	Geometry_ptr	_geometry;
	Edges_ptr		_leftBoundary;
	Edges_ptr		_rightBoundary;

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm,
		const Application &s);

	friend std::ostream& operator<<(std::ostream &strm,
		const Application_ptr &s);

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
	Geometry_ptr	getGeometry();
	Edges_ptr		left();
	Edges_ptr		right();
};

#endif