#ifndef JOB_H
#define JOB_H

using namespace std;

#include <memory>
#include <string>
#include "application.h"
#include "solution.h"
#include "specification.h"

class Job;
typedef shared_ptr<Job> Job_ptr;

class Job
{
private:
	// Constructors
	Job(Specification &spec);

	// Member variables (private)
	Specification	_spec;
	Application_ptr	_application;
	Solution_ptr	_solution;

public:
	// Factories
	static Job_ptr create(Specification &spec);

	// Getters
	Specification	getSpec();
	Application_ptr	getApplication();
	Solution_ptr	getSolution();
};

#endif