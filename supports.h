#ifndef SUPPORTS_H
#define SUPPORTS_H

using namespace std;

#include <memory>
#include "plan.h"

class Supports;
typedef shared_ptr<Supports> Supports_ptr;

class Supports
{
private:
	// Constructors
	Supports(Plan_ptr &plan);

	// Member variables (private)
	Plan_ptr _plan;

public:
	// Factories
	static Supports_ptr create(Plan_ptr &plan);

	// Getters
	Plan_ptr getPlan();
};

#endif