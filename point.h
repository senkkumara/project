#ifndef POINT_H
#define POINT_H

using namespace std;

#include <memory>
#include <ostream>
#include <vector>

class Point
{
private:
	Point(double, double, double);
	Point(std::vector<double>);
	std::vector<double> _coords;
	friend std::ostream &operator<<(std::ostream &strm, const Point &p);
	friend bool operator==(Point &cP1, Point &cP2);
	friend bool operator!=(Point &cP1, Point &cP2);
public:
	~Point();
	static shared_ptr<Point> create(double, double, double);
	static shared_ptr<Point> create(vector<double>);
	double getX();
	double getY();
	double getZ();
};

typedef shared_ptr<Point> Point_ptr;

#endif