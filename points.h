#ifndef POINTS_H
#define POINTS_H

/**
 *	points.h
 *	-----------------------------------------------------------------------
 *	A Points object is container for one or more Point objects.
 */

using namespace std;

#include <memory>
#include <ostream>
#include <vector>
#include "point.h"
#include "collection.h"

class Points;
typedef shared_ptr<Points> Points_ptr;

class Points : public Collection<Point_ptr>
{
private:
	// Constructors
	Points();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Points &ps);
	friend std::ostream &operator<<(std::ostream &strm,
		const Points_ptr &ps);

public:
	// Factories
	static Points_ptr create();
	
	// Member functions (public)
	void		transform(double matrix[4][4]);
	void		mirrorX();
	void		mirrorY();
	void		mirrorZ();
	void		mirrorComponent(int index);
};

struct PointPair
{
	Point_ptr	point1;
	Point_ptr	point2;
	double		dist;
};

#endif