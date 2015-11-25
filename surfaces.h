#ifndef SURFACES_H
#define SURFACES_H

using namespace std;

#include <memory>
#include <vector>
#include "rises.h"
#include "rise.h"
#include "layers.h"
#include "layer.h"

class Surfaces;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Surfaces> Surfaces_ptr;

class Surfaces
{
private:
	// Constructors
	Surfaces();
	Surfaces(Geometry_ptr &geometry);

	// Sub-classes
	class BoundaryBuilderSnapshot;
	typedef shared_ptr<BoundaryBuilderSnapshot> 
		BoundaryBuilderSnapshot_ptr;

	// Fields (private)
	Layers_ptr	_layers;
	Rises_ptr	_rises;
	Edges_ptr	_left;
	Edges_ptr	_right;

	// Methods (private)
	void		_init();
	void		_build(Geometry_ptr &geometry);
	void		_checkBuild();
	void		_findInterfaces();
	void		_findInterface(Rise_ptr &rise);
	void		_checkInterfaces();
	void		_findBoundaries();
	void		_findBoundary(Layer_ptr &layer);

	BoundaryBuilderSnapshot_ptr		_findNextBoundaryEdge(
		BoundaryBuilderSnapshot_ptr &snapshot,
		Edges_ptr &edges, Points_ptr &points,
		Edge_ptr &entry, Edge_ptr &exit,
		Point_ptr current[2], Edges_ptr boundaries[2]);

	void		_findBoundary(Rise_ptr &rise);
	Edges_ptr	_findInboundConnections(Edges_ptr &edges,
		Point_ptr &point);

	Edge_ptr	_findShortestInboundConnection(Rise_ptr &rise,
		Point_ptr &point);

	void		_checkBoundaries();
	void		_collectBoundaries();
	void		_categorise();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Surfaces &s);

	friend std::ostream &operator<<(std::ostream &strm,
		const Surfaces_ptr &s);

	/**
	 *	Sub-class used for tracking snapshots of building the boundary edges.
	 */
	class BoundaryBuilderSnapshot
	{
	private:
		// Constructors
		BoundaryBuilderSnapshot();
		BoundaryBuilderSnapshot(Point_ptr &left, Point_ptr &right,
			Point_ptr &removedPoint, Edges_ptr &removedEdges,
			Edges_ptr &connectionsLeft, Edges_ptr &connectionsRight);

		// Fields (private)
		bool		_empty;
		Point_ptr	_previous[2];
		Point_ptr	_removedPoint;
		Edges_ptr	_removedEdges;
		Edges_ptr	_connections[2];

	public:
		// Factories
		static BoundaryBuilderSnapshot_ptr create(Point_ptr &left,
			Point_ptr &right,
			Point_ptr &removedPoint, Edges_ptr &removedEdges,
			Edges_ptr &connectionsLeft, Edges_ptr &connectionsRight);

		static BoundaryBuilderSnapshot_ptr create();

		// Methods (public)
		bool isEmpty();

		// Getters
		Point_ptr*	getPrevious();
		Point_ptr	getPreviousLeft();
		Point_ptr	getPreviousRight();
		Point_ptr	getRemovedPoint();
		Edges_ptr	getRemovedEdges();
		Edges_ptr*	getConnections();
		Edges_ptr	getConnectionsLeft();
		Edges_ptr	getConnectionsRight();
	};

public:
	// Factories
	static Surfaces_ptr create();
	static Surfaces_ptr create(Geometry_ptr &geometry);

	// methods (public)
	Edges_ptr	left();
	Edges_ptr	right();
};

#endif