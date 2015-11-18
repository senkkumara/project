using namespace std;

#include "job.h"

/**
 *	
 */
Job::Job()
{
	_mode = MODE_ITERATE;
	_application = Application::create();
	// _solution = Solution::create(_application);
}

/**
 *
 */
Job::Job(std::string &filename)
{
	_mode = MODE_CLEAN;
	_application = Application::create(filename);
	// _solution = Solution::create(_application);
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