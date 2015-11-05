#ifndef EDGE_H
#define EDGE_H

#include <memory>
#include "point.h"

class Edge;
typedef shared_ptr<Edge> Edge_ptr;

class Edge
{
private:
	// Constructors
	Edge(Point_ptr points[2]);

	// Member variables (private)
	Point_ptr	_points[2];
	double		_angles[3];

	// Member functions (private)
	void		_calculateAngles();
	double		_calculateAngle(double d1, double d2);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Edge &e);
	friend bool operator==(Edge &e1, Edge &e2);
	friend bool operator!=(Edge &e1, Edge &e2);


public:
	// Factories
	static Edge_ptr create(Point_ptr points[2]);

	// Member functions (public)
	void		invert();
	Point_ptr	left();
	Point_ptr	right();
	double		angX();
	double		angY();
	double		angZ();
	double		ang(int index);

	// Getters
	Point_ptr*	getPoints();
	double*		getAngles();
};

#endif