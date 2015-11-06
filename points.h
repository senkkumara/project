#ifndef POINTS_H
#define POINTS_H

#include <memory>
#include <ostream>
#include <vector>
#include "point.h"

class Points;
typedef shared_ptr<Points> Points_ptr;

class Points
{
private:
	// Constructors
	Points();
	Points(string &filename);

	// Variable members (private)
	vector<Point_ptr>	_items;
	string				_filename;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Points &ps);

public:
	// Factories
	static Points_ptr create();
	static Points_ptr create(string &filename);
	
	// Member functions (public)
	void		add(Point_ptr &point);
	void		remove(Point_ptr point);
	Point_ptr	get(int index);
	int			size();
	void		transform(double matrix[4][4]);
	void		mirrorX();
	void		mirrorY();
	void		mirrorZ();
	void		mirrorComponent(int index);

	// Getters
	vector<Point_ptr> getItems();
};

struct PointPair
{
	Point_ptr point1;
	Point_ptr point2;
	double dist;
};

#endif