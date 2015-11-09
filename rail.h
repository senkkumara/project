#ifndef RAIL_H
#define RAIL_H

using namespace std;

#include <memory>
#include "plan.h"

class Rail;
typedef shared_ptr<Rail> Rail_ptr;

class Rail
{
private:
	// Constructors
	Rail(Plan_ptr &plan);

	// Member variables (private)
	Plan_ptr _plan;

public:
	// Factories
	Rail_ptr create(Plan_ptr &plan);

	// Getters
	Plan_ptr getPlan();
};

#endif