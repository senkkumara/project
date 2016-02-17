#ifndef POINT_H
#define POINT_H

/**
 *	point.h
 *	---------------------------------------------------------------------------
 *	A point object represents a point located in 3D space. It is one of the
 *	three geometry objects used to model an application - also see "facet"
 *	and "edge".
 */

using namespace std;

#include <memory>
#include <ostream>
#include <vector>

class Point;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Point> Point_ptr;

/**
 *	Represents a location in 3D space.
 */
class Point
{
private:
	// Friends
	friend class Points;

	// Constructors
	Point(double xcoord, double ycoord, double zcoord);
	Point(std::vector<double> &coords);

	// Fields (private)
	std::vector<double> _coords;

	// Methods (private)
	double	_getComponent(int index);
	void	_setComponent(int index, double value);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Point &p);
	friend std::ostream &operator<<(std::ostream &strm,	const Point_ptr &p);
	friend bool operator==(Point &p1, Point &p2);
	friend bool operator!=(Point &p1, Point &p2);
	friend bool operator==(Point_ptr &p1, Point_ptr &p2);
	friend bool operator!=(Point_ptr &p1, Point_ptr &p2);

public:
	// Factories
	static Point_ptr create(double xcoord, double ycoord, double zcoord);
	static Point_ptr create(std::vector<double> &coords);

	// Methods (public)
	void	getMatrix(double matrix[4]);
	double	getX();
	double	getY();
	double	getZ();
	void	setX(double value);
	void	setY(double value);
	void	setZ(double value);
};

#endif