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

class Points : public Collection<Point_ptr, Points_ptr>
{
private:
	// Constructors
	Points();

	// Methods (private)
	void _mirrorComponent(int index);

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Points &ps);
	friend std::ostream &operator<<(std::ostream &strm,
		const Points_ptr &ps);

public:
	// Factories
	static Points_ptr create();
	
	// Methods (public)
	void mirrorX();
	void mirrorY();
	void mirrorZ();
	void transform(double matrix[4][4]);
};

#endif