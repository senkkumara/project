#ifndef SLOT_H
#define SLOT_H

/**
 *	slot.h
 *	---------------------------------------------------------------------------
 *	A Slot object defines a point or range along the rail path where another
 *	object (e.g. Support) can reside.
 */

using namespace std;

#include <memory>

class Slot;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Slot> Slot_ptr;

/**
 *	A point or range along rail length where an object can reside (e.g.
 *	Support)
 */
class Slot
{
public:
	// Enumerations
	typedef enum Type
	{
		SLOT_TYPE_POINT,
		SLOT_TYPE_RANGE
	};

private:
	// Constructors
	Slot(double val);
	Slot(double min, double max);

	// Fields (private)
	Type	_type;
	double	_range[2];

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Slot &s);
	friend std::ostream &operator<<(std::ostream &strm, const Slot_ptr &s);

public:
	// Factories
	static Slot_ptr create(double val);
	static Slot_ptr create(double min, double max);

	// Methods (public)
	Type		getType();
	double*		getRange();
	Slot_ptr	divide(double beg, double end);
};

#endif