using namespace std;

#include "solution.h"

/**
 *	(Private) Constructs an solution from a application
 *	argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Solution::Solution(Specification &spec, Application_ptr &app)
{
	_iter = 0;
	_spec = spec;
	_app = app;

	do
	{
		_iter++;
		_skeleton = Skeleton::create(_app, _spec);
		_supports = Supports::create(_app, _skeleton);
		_rails = Rails::create(_app, _skeleton, _supports);
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
							  Application_ptr &app)
{
	return Solution_ptr(new Solution(spec, app));
}

int Solution::getIteration()
{
	return _iter;
}

Specification Solution::getSpec()
{
	return _spec;
}

/**
 *	Gets the application that was used to create the solution.
 */
Application_ptr Solution::getApp()
{
	return _app;
}

Skeleton_ptr Solution::getSkeleton()
{
	return _skeleton;
}

Supports_ptr Solution::getSupports()
{
	return _supports;
}
Rails_ptr Solution::getRails()
{
	return _rails;
}