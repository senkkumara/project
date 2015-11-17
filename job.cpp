using namespace std;

#include "job.h"

/**
 *	
 */
Job::Job()
{
	_mode = MODE_ITERATE;
	_staircase = Staircase::create();
	// _installation = Installation::create(_staircase);
}

/**
 *
 */
Job::Job(std::string &filename)
{
	_mode = MODE_CLEAN;
	_staircase = Staircase::create(filename);
	// _installation = Installation::create(_staircase);
}

/**
 *
 */
Job_ptr Job::create()
{
	return Job_ptr(new Job());
}

/**
 *
 */
Job_ptr Job::create(std::string &filename)
{
	return Job_ptr(new Job(filename));
}