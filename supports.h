#ifndef SUPPORTS_H
#define SUPPORTS_H

/**
 *	supports.h
 *	---------------------------------------------------------------------------
 *	A Supports object is container for one or more Support objects.
 *
 *	It forms one layer of the "Solution" stack.
 *
 *	During the building of the Supports object snapshots are taken of each
 *	iteration - this is to facilitate "back-stepping".
 */

using namespace std;

#include <memory>
#include <vector>
#include "application.h"
#include "skeleton.h"
#include "support.h"
#include "slot.h"

class Supports;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Supports> Supports_ptr;

class SupportsBuilderSnapshot;		// Pre-declare class for shared pointer
									// typedef

typedef shared_ptr<SupportsBuilderSnapshot> SupportsBuilderSnapshot_ptr;

/**
 *	Responsible for tracking changes to the Supports object as it is
 *	built - facilitating "back-stepping" in the event of a failed build.
 */
class SupportsBuilderSnapshot
{
private:
	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const SupportsBuilderSnapshot &s);

	friend std::ostream &operator<<(std::ostream &strm,
		const SupportsBuilderSnapshot_ptr &s);
};

/**
 *	Container for, and responsible for building, Support objects.
 *
 *	The building is achieved as follows:
 *		1)	Create "Slots" - a slot is either a point or a range in which a
 *			support *could* exist.
 *		2)	Optimally place support in Slots.
 */
class Supports : Collection<Support_ptr, Supports_ptr>
{
private:
	// Constructors
	Supports(Application_ptr &app, Skeleton_ptr &skel);

	// Fields (private)
	Application_ptr		_app;
	Skeleton_ptr		_skeleton;
	vector<Slot_ptr>	_slots;

	// Methods (private)
	void _findSlots();
	void _allocateSlots();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Supports &s);
	friend std::ostream &operator<<(std::ostream &strm, const Supports_ptr &s);

public:
	// Factories
	static Supports_ptr create(Application_ptr &app, Skeleton_ptr &layout);

	// Methods (public)
	Application_ptr		getApp();
	Skeleton_ptr		getSkeleton();
	vector<Slot_ptr>	getSlots();
};

#endif