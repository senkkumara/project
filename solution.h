#ifndef SOLUTION_H
#define SOLUTION_H

/**
 *	solution.h
 *	---------------------------------------------------------------------------
 *	A Solution object forms one half of the Job hierachy - the other being
 *	Application. It therefore contains a hierarchy of objects that form
 *	the definition of a stairlift for a given application.
 */

using namespace std;

#include <memory>
#include "application.h"
#include "enums.h"
#include "rails.h"
#include "skeleton.h"
#include "specification.h"
#include "supports.h"

class Solution;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Solution> Solution_ptr;

class SolutionBuilderSnapshot;		// Pre-declare class for shared pointer
									// typedef

typedef shared_ptr<SolutionBuilderSnapshot> SolutionBuilderSnapshot_ptr;

/**
 *	Contains the hierarchy of objects that define a stairlift for a given
 *	application.
 */
class Solution
{
private:
	// Constructors
	Solution(Specification &spec, Application_ptr &app, Side side);

	// Fields (private)
	Specification	_spec;
	Application_ptr	_app;
	Side			_side;
	int				_iter;
	Skeleton_ptr	_skeleton;
	Supports_ptr	_supports;
	Rails_ptr		_rails;
	double			_quality;

	// Methods (private)
	bool			_isValid();
	void			_calculateQuality();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Solution &s);
	friend std::ostream &operator<<(std::ostream &strm, const Solution_ptr &s);

public:
	// Factories
	static Solution_ptr create(Specification &spec,
		Application_ptr &app, Side side);

	// Methods (public)
	Specification	getSpecification();
	Application_ptr getApplication();
	int				getIteration();
	Skeleton_ptr	getSkeleton();
	Supports_ptr	getSupports();
	Rails_ptr		getRails();
	double			getQuality();
};

/**
 *	Responsible for tracking changes to the Solution object as it is
 *	built - facilitating "back-stepping" in the event of a failed build.
 */
class SolutionBuilderSnapshot
{
private:
	// Constructors
	SolutionBuilderSnapshot();

	// Fields (private)

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm,
		const SolutionBuilderSnapshot &s);

	friend std::ostream &operator<<(std::ostream &strm,
		const SolutionBuilderSnapshot_ptr &s);

public:
	// Factories
	static SolutionBuilderSnapshot_ptr create();

	// Methods (public)
};

#endif