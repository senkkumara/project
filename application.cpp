/**
 *	application.cpp
 *	-----------------------------------------------------------------------
 *	See "application.h" for a description.
 */

using namespace std;

#include "application.h"
#include <iostream>
#include <string>
#include "facet.h"
#include "exceptions.h"

/**
 *	(Private) Constructs an application from facets retrieved from
 *	a text file argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Application::Application(Specification &spec)
{
	// Construct geometry
	_filename = spec.Filename;
	_geometry = Geometry::create(_filename);
	_surfaces = Surfaces::create(_geometry);

	// Expose key items from Surfaces
	_boundary[0] = _surfaces->left();
	_boundary[1] = _surfaces->right();
	_nosings = _surfaces->getNosings();
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application &a)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Application");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application_ptr &a)
{
	return strm << *a;
}

/**
 *	Factory method using constructor that takes a filename as an argument.
 */
Application_ptr Application::create(Specification &spec)
{
	return Application_ptr(new Application(spec));
}

/**
 *	Get the filename the application was created from.
 */
std::string Application::getFilename()
{
	return _filename;
}

/**
 *	Get the surface the application comprises of.
 */
Surfaces_ptr Application::getSurfaces()
{
	return _surfaces;
}

/**
 *	Get the geometry the application comprises of.
 */
Geometry_ptr Application::getGeometry()
{
	return _geometry;
}

/**
 *	Get the boundary the application comprises of.
 */
Edges_ptr* Application::getBoundary()
{
	return _boundary;
}

/**
 *	Get the edges comprising the left boundary.
 */
Edges_ptr Application::left()
{
	return _boundary[0];
}

/**
 *	Get the edges comprising the right boundary.
 */
Edges_ptr Application::right()
{
	return _boundary[1];
}

/**
 *	Get the nosings the application comprises of.
 */
Edges_ptr Application::getNosings()
{
	return _nosings;
}