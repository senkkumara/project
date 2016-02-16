#ifndef SKELETON_H
#define SKELETON_H

/**
 *	skeleton.h
 *	---------------------------------------------------------------------------
 *	A Skeleton object is responsible for managing the objects that build and
 *	represent datum curves to represent the paths of the rails.
 */

using namespace std;

#include <memory>
#include "application.h"
#include "collection.h"
#include "enums.h"
#include "plan.h"
#include "path.h"

class Skeleton;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Skeleton> Skeleton_ptr;

class SkeletonBuilderSnapshot;		// Pre-declare class for shared pointer
									// typedef

typedef shared_ptr<SkeletonBuilderSnapshot> SkeletonBuilderSnapshot_ptr;

/**
 *	Manages objects responsible for creating datum curves representing the 
 *	upper and lower rails.
 */
class Skeleton
{
public:
	// Factories
	static Skeleton_ptr create(Application_ptr &app, Specification &spec,
		Side side);

	// Methods (public)
	int					getIteration();
	Application_ptr		getApplication();
	Specification		getSpecification();
	Side				getSide();
	Plan_ptr			getPlan();
	Path_ptr*			getPaths();
	Path_ptr			getLower();
	Path_ptr			getUpper();

private:
	// Constructors
	Skeleton(Application_ptr &app, Specification &spec, Side side);

	// Fields (private)
	int					_iter;		// Track iterative attempts to build
	Application_ptr		_app;		// Geometry to build skeleton on
	Specification		_spec;		// Additional app details
	Side				_side;
	Plan_ptr			_plan;
	Path_ptr			_path[2];

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const Skeleton &p);

	friend std::ostream &operator<<(std::ostream &strm,
		const Skeleton_ptr &p);
};

/**
 *	Responsible for tracking changes to the Skeleton object as it is
 *	built - facilitating "back-stepping" in the event of a failed build.
 */
class SkeletonBuilderSnapshot
{
public:
	// Factories
	static SkeletonBuilderSnapshot_ptr create();

	// Methods (public)
	bool isValid();

private:
	// Constructors
	SkeletonBuilderSnapshot();

	// Fields (private)
	PlanBuilderSnapshot_ptr _planSnap;
	PathBuilderSnapshot_ptr _lowerSnap;
	PathBuilderSnapshot_ptr _upperSnap;

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const SkeletonBuilderSnapshot &s);

	friend std::ostream &operator<<(std::ostream &strm,
		const SkeletonBuilderSnapshot_ptr &s);
};

#endif