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
 *	(Private) Constructs a application from the file currently
 *	in session.
 *
 *	Do not use this directly, use the provided factory method.
 */
Application::Application()
{
	// do nothing...
}

/**
 *	(Private) Constructs a application from facets retrieved from
 *	a text file argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Application::Application(std::string &filename)
{
	_filename = filename;
	_geometry = Geometry::create(_filename);
	//_surfaces = Surfaces::create(_geometry);
	//_features = Features::create(_surface);
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application &s)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Application");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Application_ptr &s)
{
	return strm << *s;
}

/**
 *	Factory method using the default constructor
 */
Application_ptr Application::create()
{
	return Application_ptr(new Application());
}

/**
 *	Factory method using constructor that takes a filename as
 *	an argument.
 */
Application_ptr Application::create(string &filename)
{
	return Application_ptr(new Application(filename));
}

/**
 *	Get the filename the application was created from.
 */
std::string Application::getFilename()
{
	return _filename;
}

/**
 *	Get the features the application comprises of.
 */
Features_ptr Application::getFeatures()
{
	return _features;
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
 *	Get the edges comprising the left boundary.
 */
Edges_ptr Application::left()
{
	return _leftBoundary;
}

/**
 *	Get the edges comprising the right boundary.
 */
Edges_ptr Application::right()
{
	return _rightBoundary;
}