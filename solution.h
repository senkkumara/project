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
#include "specification.h"
#include "application.h"
#include "skeleton.h"
#include "supports.h"
#include "rails.h"

class Solution;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Solution> Solution_ptr;

/**
 *	Contains the hierarchy of objects that define a stairlift for a given
 *	application.
 */
class Solution
{
private:
	// Constructors
	Solution(Specification &spec, Application_ptr &app);

	// Fields (private)
	int				_iter;
	Specification	_spec;
	Application_ptr	_app;
	Skeleton_ptr	_skeleton;
	Supports_ptr	_supports;
	Rails_ptr		_rails;

	// Methods (private)
	bool _isValid();

	// Operator overloads
	friend std::ostream &operator<<(std::ostream &strm, const Solution &s);
	friend std::ostream &operator<<(std::ostream &strm, const Solution_ptr &s);

public:
	// Factories
	static Solution_ptr create(Specification &spec,
		Application_ptr &app);

	// Methods (public)
	int				getIteration();
	Specification	getSpec();
	Application_ptr getApp();
	Skeleton_ptr	getSkeleton();
	Supports_ptr	getSupports();
	Rails_ptr		getRails();
};

#endif