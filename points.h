#ifndef POINTS_H
#define POINTS_H

/**
 *	points.h
 *	---------------------------------------------------------------------------
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

/**
 *	Collection of Points.
 */
class Points : public Collection<Point_ptr, Points_ptr>
{
private:
	// Constructors
	Points();
	Points(vector<Point_ptr> &ps);

	// Methods (private)
	void _mirrorComponent(int index);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Points &p);
	friend std::ostream &operator<<(std::ostream &strm,
		const Points_ptr &p);

public:
	// Factories
	static Points_ptr create();
	static Points_ptr create(vector<Point_ptr> &ps);
	
	// Methods (public)
	void mirrorX();
	void mirrorY();
	void mirrorZ();
};

#endif