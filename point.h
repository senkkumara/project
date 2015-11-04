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
	Point(double, double, double);
	Point(std::vector<double>);

	// Member variables (private)
	std::vector<double> _coords;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Point &p);
	friend bool operator==(Point &cP1, Point &cP2);
	friend bool operator!=(Point &cP1, Point &cP2);
public:
	~Point();

	// Factories
	static shared_ptr<Point> create(double, double, double);
	static shared_ptr<Point> create(vector<double>);

	// Getters
	double getX();
	double getY();
	double getZ();
};

typedef shared_ptr<Point> Point_ptr;

#endif