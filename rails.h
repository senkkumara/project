#ifndef RAILS_H
#define RAILS_H

/**
 *	rails.h
 *	---------------------------------------------------------------------------
 *	A Rails object is container for one or more Rail objects.
 *
 *	It forms one layer of the "Solution" stack.
 *
 *	During the building of the Rails object snapshots are taken of each
 *	iteration - this is to facilitate "back-stepping".
 */

using namespace std;

#include <memory>
#include <vector>
#include "application.h"
#include "skeleton.h"
#include "supports.h"
#include "slot.h"
#include "section.h"

class Rails;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Rails> Rails_ptr;

class RailsBuilderSnapshot;		// Pre-declare class for shared pointer
								// typedef

typedef shared_ptr<RailsBuilderSnapshot> RailsBuilderSnapshot_ptr;

/**
 *	Container for, and responsible for building, Rail objects.
 *
 *	The building is achieved as follows:
 *		1)	Create "Slots" - a slot is either a point or a range in which a
 *			connection between rails *could* exist.
 *		2)	Optimally place connections in Slots.
 */
class Rails : Collection<Section_ptr, Rails_ptr>
{
private:
	// Constructors
	Rails(Application_ptr &app, Skeleton_ptr &skel, Supports_ptr &sup);

	// Fields (private)
	Application_ptr		_app;
	Skeleton_ptr		_skeleton;
	Supports_ptr		_supports;
	vector<Slot_ptr>	_slots;

	// Methods (private)
	void _findSlots();
	void _allocateSlots();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Rails &r);
	friend std::ostream &operator<<(std::ostream &strm, const Rails_ptr &r);

public:
	// Factories
	static Rails_ptr create(Application_ptr &app, Skeleton_ptr &skel,
		Supports_ptr &sup);

	// Methods (public)
	Application_ptr		getApp();
	Skeleton_ptr		getSkeleton();
	Supports_ptr		getSupports();
	vector<Slot_ptr>	getSlots();
};

/**
 *	Responsible for tracking changes to the Rails object as it is
 *	built - facilitating "back-stepping" in the event of a failed build.
 */
class RailsBuilderSnapshot
{
private:
	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const RailsBuilderSnapshot &r);

	friend std::ostream &operator<<(std::ostream &strm,
		const RailsBuilderSnapshot_ptr &r);
};

#endif