using namespace std;

#include <memory>
#include "geometry.h"
#include "edges.h"
#include "edge.h"

class Surface
{
private:
	// Methods (private)
	void	_init();

protected:
	// Fields (protected)
	Geometry_ptr	_geometry;
	Edge_ptr		_entry;
	Edge_ptr		_exit;
	Edges_ptr		_left;
	Edges_ptr		_right;
	double			_ifcAngle;

public:
	// Methods (public)
	void		recalculateIfcAngle();
	Edge_ptr	entry();
	Edge_ptr	exit();
	Edges_ptr	left();
	Edges_ptr	right();
	void		invertEntry();
	void		invertExit();

	// Getters
	double			getIfcAngle();
	Geometry_ptr	getGeometry();

	// Setters
	void setEntry(Edge_ptr edge);
	void setExit(Edge_ptr edge);

};