#ifndef SOLUTION_H
#define SOLUTION_H

using namespace std;

#include <memory>
#include "specification.h"
#include "application.h"
#include "skeleton.h"
#include "supports.h"
#include "rails.h"

class Solution;		// Pre-declare class for shared pointer typedef
typedef shared_ptr<Solution> Solution_ptr;

class Solution
{
private:
	// Constructors
	Solution(Specification &spec, Application_ptr &application);

	// Fields (private)
	int				_iter;
	Specification	_spec;
	Application_ptr	_application;
	Skeleton_ptr	_skeleton;
	Supports_ptr	_supports;
	Rails_ptr		_rails;

	// Methods (private)
	bool _isValid();

public:
	// Factories
	static Solution_ptr create(Specification &spec,
		Application_ptr &application);

	// Getters
	int				getIteration();
	Specification	getSpec();
	Application_ptr getApplication();
	Skeleton_ptr	getSkeleton();
	Supports_ptr	getSupports();
	Rails_ptr		getRails();
};

#endif