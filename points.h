#ifndef POINTS_H
#define POINTS_H

#include <memory>
#include <ostream>
#include <vector>
#include "point.h"

class Points
{
private:
	Points(string &filename);
	vector<Point_ptr> _items;
	friend std::ostream &operator<<(std::ostream &strm, const Points &ps);
public:
	~Points();
	static shared_ptr<Points> create(string &filename);
	vector<Point_ptr> getItems();
	void add(Point_ptr pnt);
	void remove(Point_ptr pnt);
	Point_ptr get(int index);
	int size();
	void transform(double dx, double dy, double dth);
};

typedef shared_ptr<Points> Points_ptr;

#endif