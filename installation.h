#ifndef INSTALLATION_H
#define INSTALLATION_H

using namespace std;

#include <memory>
#include "staircase.h"
#include "plan.h"
#include "supports.h"

class Installation;
typedef shared_ptr<Installation> Installation_ptr;

class Installation
{
private:
	// Constructors
	Installation(Staircase_ptr &staircase);

	// Member variables (private)
	Staircase_ptr	_staircase;
	Plan_ptr		_plan;
	Supports_ptr	_supports;

public:
	// Factories
	Installation_ptr create(Staircase_ptr &staircase);

	// Getters
	Staircase_ptr getStaircase();
};

#endif