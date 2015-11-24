using namespace std;

#include "solution.h"

/**
 *	(Private) Constructs an solution from a application
 *	argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Solution::Solution(Specification &spec, Application_ptr &application)
{
	_spec = spec;
	_application = application;

	do
	{
		_plan = Plan::create(_application);
		_supports = Supports::create(_plan);
		_rails = Rails::create(_plan);
	}
	while (! _isValid());
}

bool Solution::_isValid()
{
	//TODO: Implement...
	return true;
}

/**
 *	Factory method using the constructor with a application 
 *	argument.
 */
Solution_ptr Solution::create(Specification &spec,
							  Application_ptr &application)
{
	return Solution_ptr(new Solution(spec, application));
}

Specification Solution::getSpec()
{
	return _spec;
}

/**
 *	Gets the application that was used to create the solution.
 */
Application_ptr Solution::getApplication()
{
	return _application;
}

Plan_ptr Solution::getPlan()
{
	return _plan;
}

Supports_ptr Solution::getSupports()
{
	return _supports;
}
Rails_ptr Solution::getRails()
{
	return _rails;
}