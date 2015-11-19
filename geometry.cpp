/**
 *	geometry.cpp
 *	-----------------------------------------------------------------------
 *	See "geometry.h" for a description.
 */

using namespace std;

#include "geometry.h"
#include <memory>
#include <sstream>
#include "exceptions.h"

/**
 *	(Private) Default constructor.
 *
 *	Do not use this directly, use the provided factory method.
 */
Geometry::Geometry()
{
	_init();
}

/**
 *	(Private) Constructs geometry from the file currently
 *	in session.
 *
 *	Do not use this directly, use the provided factory method.
 */
Geometry::Geometry(std::string &filename)
{
	_init();
	_filename = filename;
	_categoriseInput(_filename);

	switch (_type)
	{
	case GEOM_FACET:
		_facets = Facets::create(_filename);
		break;
	case GEOM_POINT:
		_points = Points::create(_filename);
		break;
	}
}

void Geometry::_init()
{
	_facets = Facets::create();
	_edges = Edges::create();
	_points = Points::create();
}

/**
 *	(Private) Based on the extension of the filename argument, determine
 *	how the geometry is to be built (e.g. facet- or point-based).
 */
void Geometry::_categoriseInput(std::string &filename)
{
	// Check file has an extension
	if (filename.find(".") == std::string::npos)
	{
		throw UnsupportedFileTypeException("NO EXTENSION");
	}

	std::stringstream ss(filename);
	std::size_t index = filename.find_last_of(".");
	std::string ext = filename.substr(index + 1);

	// Make uppercase to help comparison
	for (auto & c: ext) c = toupper(c);

	// Check for valid file extension
	if (ext == "STL")
	{
		_fileType = FILE_STL;
		_type = GEOM_FACET;
	}
	else if (ext == "DXF")
	{
		_fileType = FILE_DXF;
		_type = GEOM_FACET;
	}
	else if (ext == "PTS")
	{
		_fileType = FILE_PTS;
		_type = GEOM_POINT;
	}
	else
	{
		throw UnsupportedFileTypeException(ext);
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Geometry &g)
{
	//TODO: Implement method
	throw MethodNotImplementedException("<< Geometry");
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Geometry_ptr &g)
{
	return strm << *g;
}

/**
 *	Factory method utilising the default constructor.
 */
Geometry_ptr Geometry::create()
{
	return Geometry_ptr(new Geometry());
}

/**
 *	Factory method utilising the string filename constructor.
 */
Geometry_ptr Geometry::create(std::string &filename)
{
	return Geometry_ptr(new Geometry(filename));
}

/**
 *	Get the type of geometry captured by this object.
 */
GeometryType Geometry::getType()
{
	return _type;
}

/**
 *	Get the facets the geometry comprises of.
 */
Facets_ptr Geometry::getFacets()
{
	return _facets;
}

/**
 *	Get the edges the geometry comprises of.
 */
Edges_ptr Geometry::getEdges()
{
	return _edges;
}

/**
 *	Get the edges the points comprises of.
 */
Points_ptr Geometry::getPoints()
{
	return _points;
}