using namespace std;

#include "surface.h"
#include "exceptions.h"

/**
 *	(Private) Initialises the member variables.
 */
void Surface::_init()
{
	_geometry = Geometry::create();
}

/**
 *	Calculate the angle between the entry and the exit of the layer.
 *	The origin of the rotation is the entry edge.
 */
void Surface::recalculateIfcAngle()
{
	if (_entry && _exit)
	{
		Point_ptr origin = _entry->left();
		double x1, y1,x2, y2, xOr, yOr, rot,
			xDash1, yDash1, xDash2, yDash2, dx, dy;
		
		// Get origin (distance to translate by)
		xOr = origin->getX();
		yOr = origin->getY();

		// Get angle to rotate by
		rot = _entry->getZAng();

		// Get pre-transformed points
		x1 = _exit->left()->getX();
		y1 = _exit->left()->getY();
		x2 = _exit->right()->getX();
		y2 = _exit->right()->getY();

		// Translate and rotate the points about the origin
		xDash1 = ((x1 - xOr) * cos(rot)) + ((y1 - yOr) * sin(rot));
		xDash2 = ((x2 - xOr) * cos(rot)) + ((y2 - yOr) * sin(rot));
		yDash1 = ((y1 - xOr) * cos(rot)) - ((x1 - yOr) * sin(rot));
		yDash2 = ((y2 - xOr) * cos(rot)) - ((x2 - yOr) * sin(rot));

		// Calculate the deltas
		dx = xDash2 - xDash1;
		dy = yDash2 - yDash1;

		// Calculate angle
		_ifcAngle = atan2(dy, dx);
	}
	else
	{
		// Must be first or last layer, therefore there is no angle since
		// the layer only has an exit or entry respectively.
		_ifcAngle = 0;
	}
}

/**
 *	Get the entry edge for the surface.
 */
Edge_ptr Surface::entry()
{
	return _entry;
}

/**
 *	Get the exit edge for the surface.
 */
Edge_ptr Surface::exit()
{
	return _exit;
}

/**
 *	Get the left boundary for the surface.
 */
Edges_ptr Surface::left()
{
	return _left;
}

/**
 *	Get the right boundary for the surface.
 */
Edges_ptr Surface::right()
{
	return _right;
}

/**
 *	Swaps the points at the ends of the edges that form the entry to the
 *	layer.
 *
 *	Use this instead of point->invert() to ensure the layer angle is
 *	recalculated.
 */
void Surface::invertEntry()
{
	_entry->invert();
	recalculateIfcAngle();
}

/**
 *	Swaps the points at the ends of the edges that form the exit to the
 *	layer.
 *
 *	Use this instead of point->invert() to ensure the layer angle is
 *	recalculated.
 */
void Surface::invertExit()
{
	_exit->invert();
	recalculateIfcAngle();
}

/**
 *	Adds a facet to the surface.
 */
void Surface::add(Facet_ptr &facet)
{
	_geometry->add(facet);
}

/**
 *	Removes a facet from the surface.
 */
void Surface::remove(Facet_ptr facet)
{
	_geometry->remove(facet);
}

/**
 *	Returns bool depending on whether a facet is on
 *	this surface.
 */
bool Surface::has(Facet_ptr &facet)
{
	return _geometry->getFacets()->contains(facet);
}

/**
 *	Adds a edge to the surface.
 */
void Surface::add(Edge_ptr &edge)
{
	_geometry->add(edge);
}

/**
 *	Removes a edge from the surface.
 */
void Surface::remove(Edge_ptr edge)
{
	_geometry->remove(edge);
}

/**
 *	Returns bool depending on whether a edge is on
 *	this surface.
 */
bool Surface::has(Edge_ptr &edge)
{
	return _geometry->getEdges()->contains(edge);
}

/**
 *	Adds a point to the surface.
 */
void Surface::add(Point_ptr &point)
{
	_geometry->add(point);
}

/**
 *	Removes a point from the surface.
 */
void Surface::remove(Point_ptr point)
{
	_geometry->remove(point);
}

/**
 *	Returns bool depending on whether a point is on
 *	this surface.
 */
bool Surface::has(Point_ptr &point)
{
	return _geometry->getPoints()->contains(point);
}

/**
 *	Returns bool depending on whether a facet should be on
 *	this surface.
 */
bool Surface::onSurface(Facet_ptr &facet)
{
	return facet->getMaxZ() <= _maxHeight &&
		facet->getMinZ() >= _minHeight;
}

/**
 *	Returns bool depending on whether a point should be on
 *	this surface.
 */
bool Surface::onSurface(Edge_ptr &edge)
{
	//TODO: implement function
	throw MethodNotImplementedException("Surface::onSurface");
	return false;
}

/**
 *	Returns bool depending on whether a point should be on
 *	this surface.
 */
bool Surface::onSurface(Point_ptr &point)
{
	return point->getZ() <= _maxHeight &&
		point->getZ() >= _minHeight;
}

/**
 *	Get the interface angle for the surface.
 */
double Surface::getIfcAngle()
{
	return _ifcAngle;
}

/**
 *	Get the geometry of the surface.
 */
Geometry_ptr Surface::getGeometry()
{
	return _geometry;
}

/**
 *	Get the tolerance.
 */
double Surface::getHeightTol()
{
	return _tol;
}

/**
 *	Get the minimum z-value for this layer.
 */
double Surface::getMinHeight()
{
	return _minHeight;
}

/**
 *	Get the maximum z-value for this layer.
 */
double Surface::getMaxHeight()
{
	return _maxHeight;
}

double Surface::getAvgHeight()
{
	return (_minHeight + _maxHeight) / 2;
}

/** 
 *	Set the entry edge of the surface.
 */
void Surface::setEntry(Edge_ptr edge)
{
	_entry = edge;
	recalculateIfcAngle();
}

/**
 *	Set the exit edge of the surface.
 */
void Surface::setExit(Edge_ptr edge)
{
	_exit = edge;
	recalculateIfcAngle();
}