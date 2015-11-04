#ifndef POINT_H
#define POINT_H

using namespace std;

#include <memory>
#include <ostream>
#include <vector>

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
	static shared_ptr<Point> create(double xcoord, 
									double ycoord,
									double zcoord);

	static shared_ptr<Point> create(vector<double> &coords);

	// Getters
	double getX();
	double getY();
	double getZ();
	double getComponent(int index);
};

typedef shared_ptr<Point> Point_ptr;

#endif