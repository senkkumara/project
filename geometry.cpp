/**
 *	geometry.cpp
 *	-----------------------------------------------------------------------
 *	See "geometry.h" for a description.
 */

using namespace std;

#include "geometry.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
	_categoriseInput();
	_build();
}

/**
 *	(Private) Initialises the key fields for the Geometry object.
 */
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
void Geometry::_categoriseInput()
{
	// Check file has an extension
	if (_filename.find(".") == std::string::npos)
	{
		throw UnsupportedFileTypeException("NO EXTENSION");
	}

	std::stringstream ss(_filename);
	std::size_t index = _filename.find_last_of(".");
	std::string ext = _filename.substr(index + 1);

	// Make uppercase to help comparison
	for (auto & c: ext) c = toupper(c);

	// Check for valid file extension
	if (ext == "STL")
	{
		_fileType = FILE_STL;
	}
	else if (ext == "DXF")
	{
		_fileType = FILE_DXF;
	}
	else
	{
		throw UnsupportedFileTypeException(ext);
	}
}

/**
 *	(Private) Extract the geometry from the provided file.
 */
void Geometry::_build()
{
	switch (_fileType)
	{
	case FILE_STL:
		_buildFromSTL();
		break;
	case FILE_DXF:
		_buildFromDXF();
		break;
	}
}

/**
 *	(Private) Extract the geometry from the provided DXF file.
 */
void Geometry::_buildFromDXF()
{
	//TODO: implement method
	throw MethodNotImplementedException("Facets::_extractFromDXF");
}

/**
 *	(Private) Extract the geometry from the provided STL file.
 */
void Geometry::_buildFromSTL()
{
	std::string line;
	ifstream file(_filename);
	
	if (!file.is_open())
	{
		// File could not be opened
		throw FileNotFoundException();
	}

	Facet_ptr facet;
	Edge_ptr tempEdge;
	Point_ptr point;
	Point_ptr tempPoint;
	Point_ptr points[3];
	Edge_ptr edges[3];
	double normals[3];
	std::string facetPrefix = "facet normal ";
	std::string vertexPrefix = "vertex ";

	// Each pass through the following loop should process all the lines
	// that a facet comprises of in a STL file.
	//
	// Note the STL format is as follows:
	//	solid <NAME>
	//	 facet normal <nx> <ny> <nz>
	//		 outer loop
	//		  vertex <x1> <y1> <z1>
	//		  vertex <x1> <y1> <z1>
	//		  vertex <x1> <y1> <z1>
	//		 endloop
	//	 endfacet
	//	...
	//	endsolid <NAME>
	while (getline(file, line))
	{
		// Look for start of a facet
		if (line.find("facet") != std::string::npos)
		{
			// Remove "  facet normal " prefix
			std::stringstream ss(line.substr(line.find(facetPrefix)
				+ facetPrefix.length()));

			std::string item;
			int count = 0;		// Only extract three entries (x, y, z)

			while (getline(ss, item, ' ') && count < 3)
			{
				istringstream os(item);
				os >> normals[count];
				count++;
			}
		}
		else
		{
			// Possibly "solid NAME" or "endsolid" lines
			continue;
		}

		// Check for loop start
		getline(file, line);
		if (line.find("outer loop") == std::string::npos)
		{
			throw MalformedFileException(_filename);
		}

		// Get vertices
		getline(file, line);
		int row = 0;	// Three vertices per loop
		while (row < 3)
		{	
			if (line.find("vertex") == std::string::npos)
			{
				throw MalformedFileException(_filename);
			}

			// Remove "      vertex " prefix
			std::stringstream ss(line.substr(line.find(vertexPrefix)
				+ vertexPrefix.length()));

			std::string item;
			int count = 0;		// Only extract three entries (x, y, z)
			std::vector<double> coords;

			while (getline(ss, item, ' ') && count < 3)
			{
				coords.push_back(atof(item.c_str()));
				count++;
			}

			point = Point::create(coords);

			// Ensure no duplicate points
			tempPoint = getPoints()->get(point);
			if (tempPoint)
			{
				point = tempPoint;
			}
			else
			{
				_points->add(point);
			}

			points[row] = point;

			getline(file, line);	// Get next line
			row++;
		}

		// Check for loop end
		if (line.find("endloop") == std::string::npos)
		{
			throw MalformedFileException(_filename);
		}

		// Look for the end of a facet - create facet
		getline(file, line);
		if (line.find("endfacet") != std::string::npos)
		{
			edges[0] = Edge::create(points[0], points[1]);
			edges[1] = Edge::create(points[1], points[2]);
			edges[2] = Edge::create(points[2], points[0]);

			for (int i = 0; i < 3; i++)
			{
				tempEdge = getEdges()->get(edges[i]);
				if (tempEdge)
				{
					edges[i] = tempEdge;
				}
				else
				{
					_edges->add(edges[i]);
				}
			}

			_facets->add(Facet::create(points, edges, normals));
		}
	}

	cout << "Facets: " << _facets->size() << endl;
	cout << "Edges: " << _edges->size() << endl;
	cout << "Points: " << _points->size() << endl;

	file.close();
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
 *	Adds a facet to the geometry.
 */
void Geometry::add(Facet_ptr &facet)
{
	getFacets()->add(facet);

	Edge_ptr* edges = facet->getEdges();
	Point_ptr* points = facet->getPoints();

	for (int i = 0; i < 3; i++)
	{
		if (! getEdges()->contains(edges[i])) add(edges[i]);
	}
}

/**
 *	Removes a facet from the geometry.
 */
void Geometry::remove(Facet_ptr point)
{
	getFacets()->remove(point);
}

/**
 *	Adds a edge to the geometry.
 */
void Geometry::add(Edge_ptr &edge)
{
	getEdges()->add(edge);

	Point_ptr* points = edge->getPoints();

	for (int i = 0; i < 2; i++)
	{
		if (! getPoints()->contains(points[i])) add(points[i]);
	}
}

/**
 *	Removes a edge from the geometry.
 */
void Geometry::remove(Edge_ptr edge)
{
	getEdges()->remove(edge);
}

/**
 *	Adds a point to the geometry.
 */
void Geometry::add(Point_ptr &point)
{
	getPoints()->add(point);
}

/**
 *	Removes a point from the geometry.
 */
void Geometry::remove(Point_ptr point)
{
	getPoints()->remove(point);
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