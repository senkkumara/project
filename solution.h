#ifndef SOLUTION_H
#define SOLUTION_H

using namespace std;

#include <memory>
#include "application.h"
#include "plan.h"
#include "supports.h"

class Solution;
typedef shared_ptr<Solution> Solution_ptr;

class Solution
{
private:
	// Constructors
	Solution(Application_ptr &application);

	// Member variables (private)
	Application_ptr	_application;
	Plan_ptr		_plan;
	Supports_ptr	_supports;

public:
	// Factories
	Solution_ptr create(Application_ptr &application);

	// Getters
	Application_ptr getApplication();
};

#endif