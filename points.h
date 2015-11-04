#ifndef POINTS_H
#define POINTS_H

#include <memory>
#include <ostream>
#include <vector>
#include "point.h"

class Points
{
private:
	// Constructors
	Points();
	Points(string &filename);

	// Variable members (private)
	vector<Point_ptr> _items;
	string _filename;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Points &ps);

public:
	// Factories
	static shared_ptr<Points> create();
	static shared_ptr<Points> create(string &filename);
	
	// Member functions (public)
	void add(Point_ptr &point);
	void remove(Point_ptr &point);
	Point_ptr get(int index);
	int size();
	void transform(double dx, double dy, double dth);

	// Getters
	vector<Point_ptr> getItems();
};

typedef shared_ptr<Points> Points_ptr;

#endif