#ifndef SUPPORT_H
#define SUPPORT_H

/**
 *	support.h
 *	---------------------------------------------------------------------------
 *	A Support object is a representation of a support structure
 */

using namespace std;

#include <memory>
#include "attachable.h"

class Support;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Support> Support_ptr;

/**
 *	Represents a single support structure (e.g. Stand or Strap).
 */
class Support : public Attachable
{
public:
	// Enumerations
	typedef enum Type
	{
		SUPPORT_TYPE_STAND,
		SUPPORT_TYPE_STRAP
	};

private:
	// Constructors
	Support(double pos);

	// Fields (private)
	Type	_type;
	double	_pos;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Support &r);
	friend std::ostream &operator<<(std::ostream &strm, const Support_ptr &r);
	friend bool operator==(Support &s1, Support &s2);
	friend bool operator!=(Support &s1, Support &s2);

public:
	// Factories
	static Support_ptr create(double pos);

	// Methods (public)
	Type	getType();
	double	getPos();
};

#endif