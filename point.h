#ifndef POINT_H
#define POINT_H

/**
 *	point.h
 *	-----------------------------------------------------------------------
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

class Point
{
private:
	// Constructors
	Point(double xcoord, double ycoord, double zcoord);
	Point(std::vector<double> &coords);

	// Member variables (private)
	std::vector<double> _coords;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Point &p);
	friend std::ostream &operator<<(std::ostream &strm,
		const Point_ptr &p);

	friend bool operator==(Point &cP1, Point &cP2);
	friend bool operator!=(Point &cP1, Point &cP2);
	friend bool operator==(Point_ptr &cP1, Point_ptr &cP2);
	friend bool operator!=(Point_ptr &cP1, Point_ptr &cP2);

public:
	// Factories
	static Point_ptr create(double xcoord, 
							double ycoord,
							double zcoord);

	static Point_ptr create(std::vector<double> &coords);

	// Member functions (public)
	void getMatrix(double matrix[4]);

	// Getters
	double getX();
	double getY();
	double getZ();
	double getComponent(int index);

	// Setters
	void setX(double value);
	void setY(double value);
	void setZ(double value);
	void setComponent(int index, double value);
};

#endif