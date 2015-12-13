#ifndef SUPPORT_H
#define SUPPORT_H

/**
 *	support.h
 *	---------------------------------------------------------------------------
 *	A Support object is a representation of a support structure
 */

using namespace std;

class Support;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Support> Support_ptr;

/**
 *	Represents a single support structure (e.g. Stand or Strap).
 */
class Support
{
public:
	// Enumerations
	typedef enum Type
	{
		SUPPORT_TYPE_STAND,
		SUPPORT_TYPE_STRAP
	};

private:
	// Fields (private)
	Type	_type;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Support &r);
	friend std::ostream &operator<<(std::ostream &strm, const Support_ptr &r);

public:
	// Methods (public)
	Type	getType();
};

#endif