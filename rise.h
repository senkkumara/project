#ifndef RISE_H
#define RISE_H

/**
 *	rise.h
 *	-----------------------------------------------------------------------
 *	A rise corresponds to a section of the geometry that is near vertical.
 *	Generally this connects one layer to another.
 */

using namespace std;

#include <memory>
#include <vector>
#include "geometry.h"

class Rise;
typedef shared_ptr<Rise> Rise_ptr;

class Rise
{
private:
	// Constructors
	Rise();
	Rise(Geometry_ptr &geometry);

	// Member fields (private)
	Geometry_ptr	_geometry;
	Edge_ptr		_entry;
	Edge_ptr		_exit;
	Edges_ptr		_left;
	Edges_ptr		_right;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Rise &rise);

	friend std::ostream &operator<<(std::ostream &strm,
		const Rise_ptr &rise);

	friend bool operator==(Rise &rise1, Rise &rise2);
	friend bool operator!=(Rise &rise1, Rise &rise2);
	friend bool operator==(Rise_ptr &rise1, Rise_ptr &rise2);
	friend bool operator!=(Rise_ptr &rise1, Rise_ptr &rise2);

public:
	// Factories
	static Rise_ptr create();
	static Rise_ptr create(Facet_ptr &facet);

	// Member functions (public)
	Edge_ptr		entry();
	Edge_ptr		exit();
	Edges_ptr		Left();
	Edges_ptr		right();

	// Getters
	Geometry_ptr	getGeometry();

};

#endif