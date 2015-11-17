#ifndef JOB_H
#define JOB_H

using namespace std;

#include <memory>
#include <string>
#include "staircase.h"
#include "installation.h"

enum Mode
{
	MODE_CLEAN,			// No staircase, use text file
	MODE_ITERATE		// Installation started, use CAD
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
	Staircase_ptr		_staircase;
	Installation_ptr	_installation;

public:
	// Factories
	static Job_ptr create();
	static Job_ptr create(std::string &filename);

	// Getters
	Mode				getMode();
	Staircase_ptr		getStaircase();
	Installation_ptr	getInstallation();
};

#endif