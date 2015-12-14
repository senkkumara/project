using namespace std;

#include "job.h"

/**
 *	
 */
Job::Job(Specification &spec)
{
	_spec = spec;
	_app = Application::create(spec);
	_solution = Solution::create(spec, _app);
}

/**
 *	
 */
Job_ptr Job::create(Specification &spec)
{
	return Job_ptr(new Job(spec));
}

/**
 *	
 */
Specification Job::getSpec()
{
	return _spec;
}

/**
 *	
 */
Application_ptr Job::getApp()
{
	return _app;
}

/**
 *	
 */
Solution_ptr Job::getSolution()
{
	return _solution;
}