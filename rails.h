#ifndef RAILS_H
#define RAILS_H

using namespace std;

#include <memory>
#include "plan.h"

class Rails;
typedef shared_ptr<Rails> Rails_ptr;

class Rails
{
private:
	// Constructors
	Rails(Plan_ptr &plan);

	// Member variables (private)
	Plan_ptr _plan;

public:
	// Factories
	static Rails_ptr create(Plan_ptr &plan);

	// Getters
	Plan_ptr getPlan();
};

#endif