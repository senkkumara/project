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
#include "surface.h"
#include "geometry.h"
#include "edges.h"

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
	Surface_ptr		_surface;
	Geometry_ptr	_geometry;
	Edges_ptr		_leftBoundary;
	Edges_ptr		_rightBoundary;

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm,
		const Application &a);

	friend std::ostream& operator<<(std::ostream &strm,
		const Application_ptr &a);

public:
	// Factories
	static Application_ptr create();
	static Application_ptr create(std::string &filename);

	// Getters
	std::string		getFilename();
	Features_ptr	getFeatures();
	Surface_ptr		getSurface();
	Geometry_ptr	getGeometry();
	Edges_ptr		left();
	Edges_ptr		right();
};

#endif