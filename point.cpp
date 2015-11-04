using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "point.h"

Point::Point(double xcoord = 0.0,
			 double ycoord = 0.0,
			 double zcoord = 0.0)
{
	std::vector<double> coords;
	coords.push_back(xcoord);
	coords.push_back(ycoord);
	coords.push_back(zcoord);
}

Point::Point(std::vector<double> coords)
{
	_coords = coords;
}

Point::~Point()
{
	//TODO: Add destructor
}

Point_ptr Point::create(vector<double> coords)
{
	return Point_ptr(new Point(coords));
}

double Point::getX()
{
	return _coords.at(0);
}

double Point::getY()
{
	return _coords.at(1);
}

double Point::getZ()
{
	return _coords.at(2);
}

std::ostream &operator<<(std::ostream &strm, const Point& p)
{
	return strm << '(' << p._coords.at(0) 
				<< ", " << p._coords.at(1)
				<< ", " << p._coords.at(2)
				<< ')' << endl;
}

bool operator==(Point &cP1, Point &cP2)
{
	return (cP1.getX() == cP2.getX() &&
            cP1.getY() == cP2.getY() &&
            cP1.getZ() == cP2.getZ());
}
bool operator!=(Point &cP1, Point &cP2)
{
	return !(cP1 == cP2);
}