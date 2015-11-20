using namespace std;

#include "surface.h"

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