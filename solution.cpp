using namespace std;

#include "solution.h"

/**
 *	(Private) Constructs an solution from a application
 *	argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Solution::Solution(Application_ptr &application)
{
	_application = application;
	//TODO:: Implement...
}

/**
 *	Factory method using the constructor with a application 
 *	argument.
 */
Solution_ptr Solution::create(Application_ptr &application)
{
	return Solution_ptr(new Solution(application));
}

/**
 *	Gets the application that was used to create the solution.
 */
Application_ptr Solution::getApplication()
{
	return _application;
}