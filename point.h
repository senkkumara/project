#ifndef POINT_H
#define POINT_H

using namespace std;

#include <memory>
#include <ostream>
#include <vector>

class Point;
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
	friend bool operator==(Point &cP1, Point &cP2);
	friend bool operator!=(Point &cP1, Point &cP2);

public:
	// Factories
	static Point_ptr create(double xcoord, 
							double ycoord,
							double zcoord);

	static Point_ptr create(vector<double> &coords);

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