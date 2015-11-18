#ifndef JOB_H
#define JOB_H

using namespace std;

#include <memory>
#include <string>
#include "application.h"
#include "solution.h"

enum Mode
{
	MODE_CLEAN,			// No application, use text file
	MODE_ITERATE		// Solution started, use CAD
};

class Job;
typedef shared_ptr<Job> Job_ptr;

class Job
{
private:
	// Constructors
	Job();						// "Iterate" mode
	Job(std::string &filename);	// "Clean" mode

	// Member variables (private)
	Mode				_mode;
	Application_ptr		_application;
	Solution_ptr	_solution;

public:
	// Factories
	static Job_ptr create();
	static Job_ptr create(std::string &filename);

	// Getters
	Mode				getMode();
	Application_ptr		getApplication();
	Solution_ptr	getSolution();
};

#endif