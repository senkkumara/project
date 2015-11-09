#ifndef JOB_H
#define JOB_H

using namespace std;

#include <memory>
#include <string>
#include "staircase.h"
#include "installation.h"

class Job;
typedef shared_ptr<Job> Job_ptr;

class Job
{
private:
	// Constructors
	Job(std::string &filename);

	// Member variables (private)
	Staircase_ptr		_staircase;
	Installation_ptr	_installation;

public:
	// Factories
	static Job_ptr create(std::string &filename);

	// Getters
	Staircase_ptr		getStaircase();
	Installation_ptr	getInstallation();
};

#endif