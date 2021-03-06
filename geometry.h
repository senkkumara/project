#ifndef GEOMETRY_H
#define GEOMETRY_H

/**
 *	geometry.h
 *	---------------------------------------------------------------------------
 *	A Geometry object is a container for multiple geometric object types
 *	(Points, Edges, Facets).
 */

#include <memory>
#include <vector>
#include "facets.h"
#include "edges.h"
#include "points.h"

class Geometry;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Geometry> Geometry_ptr;

/**
 *	A collection of Points, Edges and Facets.
 */
class Geometry
{
public:
	// Enumerations
	enum FileType
	{
		FILE_DXF,
		FILE_STL,
	};

private:
	// Constructors
	Geometry();
	Geometry(std::string &filename);

	// Fields (private)
	std::string		_filename;
	FileType		_fileType;
	Facets_ptr		_facets;
	Edges_ptr		_edges;
	Points_ptr		_points;

	// Methods (private)
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

	// Methods (public)
	void			add(Facet_ptr &facet);
	void			remove(Facet_ptr facet);
	void			add(Edge_ptr &edge);
	void			remove(Edge_ptr edge);
	void			add(Point_ptr &point);
	void			remove(Point_ptr point);
	int				size();
	Facets_ptr		getFacets();
	Edges_ptr		getEdges();
	Points_ptr		getPoints();
};

#endif