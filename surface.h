#ifndef SURFACE_H
#define SURFACE_H

/**
 *	surface.h
 *	---------------------------------------------------------------------------
 *	A Surface object represents a planar surface comprising of one or more
 *	Facet objects - and therefore by extension Edge and Point objects.
 */

using namespace std;

#include <memory>
#include "geometry.h"
#include "facet.h"
#include "edges.h"
#include "edge.h"
#include "point.h"

/**
 *	Collection of Facet (and composite Points and Edges) forming a planar
 *	surface.
 */
class Surface
{
private:
	// Methods (private)
	void			_init();

protected:
	// Fields (protected)
	Geometry_ptr	_geometry;
	Edge_ptr		_entry;
	Edge_ptr		_exit;
	Edges_ptr		_left;
	Edges_ptr		_right;
	double			_ifcAngle;
	double			_tol;
	double			_minHeight;
	double			_maxHeight;

public:
	// Methods (public)
	void			recalculateIfcAngle();
	Edge_ptr		entry();
	Edge_ptr		exit();
	Edges_ptr		left();
	Edges_ptr		right();
	void			invertEntry();
	void			invertExit();
	void			add(Facet_ptr &facet);
	void			remove(Facet_ptr facet);
	bool			has(Facet_ptr &facet);
	void			add(Edge_ptr &edge);
	void			remove(Edge_ptr edge);
	bool			has(Edge_ptr &edge);
	void			add(Point_ptr &point);
	void			remove(Point_ptr point);
	bool			has(Point_ptr &point);
	bool			onSurface(Facet_ptr &facet);
	bool			onSurface(Edge_ptr &edge);
	bool			onSurface(Point_ptr &point);
	bool			isEmpty();
	double			getIfcAngle();
	Geometry_ptr	getGeometry();
	double			getHeightTol();
	double			getMinHeight();
	double			getMaxHeight();
	double			getAvgHeight();
	void			setEntry(Edge_ptr &edge);
	void			setExit(Edge_ptr &edge);
	void			setLeft(Edges_ptr &edges);
	void			setRight(Edges_ptr &edges);
};

#endif