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
#include "specification.h"
#include "surfaces.h"
#include "geometry.h"
#include "edges.h"

class Application;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Application> Application_ptr;

/**
 *	Contains the hierarchy of objects that define the geometry of a
 *	staircase.
 */
class Application
{
private:
	// Constructors
	Application(Specification &spec);

	// Fields (private)
	std::string		_filename;
	Surfaces_ptr	_surfaces;
	Geometry_ptr	_geometry;
	Edges_ptr		_boundary[2];
	Edges_ptr		_nosings;

	// Methods (private)


	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm,
		const Application &a);

	friend std::ostream& operator<<(std::ostream &strm,
		const Application_ptr &a);

public:
	// Factories
	static Application_ptr create(Specification &spec);

	// Methods (public)
	std::string		getFilename();
	Surfaces_ptr	getSurfaces();
	Geometry_ptr	getGeometry();
	Edges_ptr*		getBoundary();
	Edges_ptr		left();
	Edges_ptr		right();
	Edges_ptr		getNosings();
};

#endif