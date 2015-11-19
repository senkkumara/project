#ifndef LAYER_H
#define LAYER_H

/**
 *	layer.h
 *	-----------------------------------------------------------------------
 *	A layer object contains facets, edges and points that are at a given 
 *	z-distance. Generally speaking the capture the geometry of individual
 *	steps or landings.
 */

using namespace std;

#include <memory>
#include <vector>
#include "geometry.h"
#include "facets.h"
#include "facet.h"
#include "edge.h"
#include "points.h"
#include "point.h"

class Layer;	// Pre-declare class for shared pointer typedef
typedef shared_ptr<Layer> Layer_ptr;

enum LayerType {
	LT_START,
	LT_END,
	LT_STRAIGHT,
	LT_WINDER,
	LT_WINDER_CORNER,
	LT_LANDING_FLAT,
	LT_UNKNOWN
};

class Layer
{
private:
	// Constructors
	Layer();
	Layer(Point_ptr &point);
	Layer(Facet_ptr &facet);

	// Member variables (private)
	double			_tol;
	double			_minHeight;
	double			_maxHeight;
	Facets_ptr		_facets;
	Edges_ptr		_edges;
	Points_ptr		_points;
	Edge_ptr		_entry;
	Edge_ptr		_exit;
	Edges_ptr		_left;
	Edges_ptr		_right;
	double			_ifcAngle;
	LayerType		_type;

	// Member functions (private)
	void _init();
	void _setIfcAngle();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Layer &layer);

	friend std::ostream &operator<<(std::ostream &strm,
		const Layer_ptr &layer);

	friend bool operator<(Layer &layer1, Layer &layer2);
	friend bool operator<=(Layer &layer1, Layer &layer2);
	friend bool operator==(Layer &layer1, Layer &layer2);
	friend bool operator!=(Layer &layer1, Layer &layer2);
	friend bool operator>=(Layer &layer1, Layer &layer2);
	friend bool operator>(Layer &layer1, Layer &layer2);
	friend bool operator<(Layer_ptr &layer1, Layer_ptr &layer2);
	friend bool operator<=(Layer_ptr &layer1, Layer_ptr &layer2);
	friend bool operator==(Layer_ptr &layer1, Layer_ptr &layer2);
	friend bool operator!=(Layer_ptr &layer1, Layer_ptr &layer2);
	friend bool operator>=(Layer_ptr &layer1, Layer_ptr &layer2);
	friend bool operator>(Layer_ptr &layer1, Layer_ptr &layer2);

public:
	// Factories
	static Layer_ptr create();
	static Layer_ptr create(Facet_ptr &facet);

	// Member functions (public)
	void		add(Facet_ptr &facet);
	void		remove(Facet_ptr facet);
	bool		onLayer(Facet_ptr &facet);
	bool		hasFacet(Facet_ptr &facet);
	void		add(Edge_ptr &edge);
	void		remove(Edge_ptr edge);
	bool		hasEdge(Edge_ptr &edge);
	void		add(Point_ptr &point);
	void		remove(Point_ptr point);
	bool		onLayer(Point_ptr &point);
	bool		hasPoint(Point_ptr &point);
	bool		hasOverlap(Layer_ptr &layer);
	void		invertEntry();
	void		invertExit();
	Edge_ptr	entry();
	Edge_ptr	exit();
	Edges_ptr	left();
	Edges_ptr	right();

	// Getters
	double			getHeightTol();
	double			getMinHeight();
	double			getMaxHeight();
	Facets_ptr		getFacets();
	Edges_ptr		getEdges();
	Points_ptr		getPoints();
	double			getIfcAngle();
	LayerType		getType();

	// Setters
	void setEntry(Edge_ptr edge);
	void setExit(Edge_ptr edge);
	void setType(LayerType type);
};

#endif