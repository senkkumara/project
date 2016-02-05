/**
 *	job.cpp
 *	-----------------------------------------------------------------------
 *	See "job.h" for a description.
 */

using namespace std;

#include "job.h"

/**
 *	(Private) Constructs a Job from a Specification argument.
 *
 *	Note: responsibility for creating the objects themselves is delegated
 *	to a hierarchy of sub-classes.
 */
Job::Job(Specification &spec)
{
	_spec = spec;
	_app = Application::create(spec);
	_solutions = Solutions::create(spec, _app);
}

/**
 *	Factory method using the constructor with a specification argument.
 */
Job_ptr Job::create(Specification &spec)
{
	return Job_ptr(new Job(spec));
}

/**
 *	Get the job's specification
 */
Specification Job::getSpecification()
{
	return _spec;
}

/**
 *	Get the job's application
 */
Application_ptr Job::getApplication()
{
	return _app;
}

/**
 *	Get the solutions to the job.
 *
 *	Note: a job may have multiple solutions depending on the options selected
 *	in the specification.
 */
Solutions_ptr Job::getSolutions()
{
	return _solutions;
}