#ifndef ATTACHABLE_H
#define ATTACHABLE_H

/**
 *	attachable.h
 *	---------------------------------------------------------------------------
 *	An Attachable object is one in which can be placed in a Slot on the
 *	Skeleton (e.g. Chair, Support and Connection).
 */

using namespace std;

#include <memory>

class Attachable;
typedef shared_ptr<Attachable> Attachable_ptr;

/**
 *	Generic attachable object - inherited from by specific attachable object
 *	types.
 */
class Attachable
{
private:
	// Fields (private)
	double	_pos;

public:
	// Methods (public)
	double	getPos();
};

#endif