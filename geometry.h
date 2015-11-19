#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>
#include <vector>
#include "facets.h"
#include "edges.h"
#include "points.h"

class Geometry;
typedef shared_ptr<Geometry> Geometry_ptr;

enum FileType
{
	FILE_DXF,
	FILE_STL,
};

class Geometry
{
private:
	// Constructors
	Geometry();
	Geometry(std::string &filename);

	// Member fields (private)
	std::string		_filename;
	FileType		_fileType;
	Facets_ptr		_facets;
	Edges_ptr		_edges;
	Points_ptr		_points;

	// Member functions (private)
	void	_init();
	void	_categoriseInput();
	void	_build();
	void	_buildFromSTL();
	void	_buildFromDXF();

	// Operator overloads
	friend std::ostream& operator<<(std::ostream &strm,
		const Geometry &g);

	friend std::ostream& operator<<(std::ostream &strm,
		const Geometry_ptr &g);

public:
	// Factories
	static Geometry_ptr create();
	static Geometry_ptr create(std::string &filename);

	// Getters
	Facets_ptr		getFacets();
	Edges_ptr		getEdges();
	Points_ptr		getPoints();
};

#endif