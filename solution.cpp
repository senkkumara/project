/**
 *	solution.cpp
 *	-----------------------------------------------------------------------
 *	See "solution.h" for a description.
 */

using namespace std;

#include "solution.h"

/**
 *	(Private) Constructs an solution from a application
 *	argument.
 *
 *	Do not use this directly, use the provided factory method.
 */
Solution::Solution(Specification &spec, Application_ptr &app, Side side)
{
	//TODO: implement method - include snapshot mechanism
	_iter = 0;
	_spec = spec;
	_app = app;

	do
	{
		_iter++;
		_skeleton = Skeleton::create(_app, _spec, side);
		_supports = Supports::create(_app, _skeleton);
		_rails = Rails::create(_app, _skeleton, _supports);
	}
	while (! _isValid());
}

/**
 *	(Private) Determine whether the solutions meets all of the design rules.
 */
bool Solution::_isValid()
{
	//TODO: implement method
	return true;
}

/**
 *	(Private) Recalculate the quality of the solution.
 */
void Solution::_calculateQuality()
{
	if (! _isValid())
	{
		_quality = 0;
	}
	else
	{
		//TODO: implement method
		_quality = 1;
	}
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Solution &s)
{
	//TODO: implement method
	return strm;
}

/**
 *	<< operator overload.
 */
std::ostream &operator<<(std::ostream &strm, const Solution_ptr &s)
{
	return strm << *s;
}

/**
 *	Factory method using the constructor with a Specification and an
 *	application argument.
 */
Solution_ptr Solution::create(Specification &spec,
							  Application_ptr &app, Side side)
{
	return Solution_ptr(new Solution(spec, app, side));
}

/**
 *	Get the specification for the solution.
 */
Specification Solution::getSpecification()
{
	return _spec;
}

/**
 *	Gets the application that was used to create the solution.
 */
Application_ptr Solution::getApplication()
{
	return _app;
}

/**
 *	Get the current iteration of the building of the solution.
 */
int Solution::getIteration()
{
	return _iter;
}

/**
 *	Get the skeleton from the solution.
 */
Skeleton_ptr Solution::getSkeleton()
{
	return _skeleton;
}

/**
 *	Get the supports from the solution.
 */
Supports_ptr Solution::getSupports()
{
	return _supports;
}

/**
 *	Get the rails from the solution.
 */
Rails_ptr Solution::getRails()
{
	return _rails;
}

/**
 *	Get the quality of the solution.
 */
double Solution::getQuality()
{
	return _quality;
}