using namespace std;

#define _USE_MATH_DEFINES

#include "tests.h"
#include <math.h>
#include <iostream>

const double angTol = 5 * M_PI / 180;	// 5 degrees

// Tests::Layer
TestResult Tests::Layer::isStart(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- No lower rise
	 */
	if (Tests::Structure::hasNoLowerRise(layer).result)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::Layer::isEnd(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- No upper rise
	 */
	if (Tests::Structure::hasNoUpperRise(layer).result)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::Layer::isStraightStandard(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- Four points
	 *	- Interface angle approximately 0
	 */
	if (Tests::Points::Count::isEqualTo4(layer).result &&
		Tests::Interface::Angle::isEqualTo0Unsigned(layer).result)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::Layer::isStraightExtended(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- Interface angle approximately 0
	 *	- Going approximately equal to the going
	 *	- One bounday has only one edge
	 */
	if (Tests::Interface::Angle::isEqualTo0Unsigned(layer).result &&
		Tests::Profile::isGoingLengthWithin25pcOfRiseLength(layer).result)
	{
		if (Tests::Boundary::Count::Left::isEqualTo1(layer).result ||
			Tests::Boundary::Count::Right::isEqualTo1(layer).result)
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isWinderStandard(Layer_ptr &layer)
{
	if (Tests::Points::Count::isEqualTo4(layer).result ||
		Tests::Points::Count::isEqualTo3(layer).result)
	{
		if (Tests::Interface::Angle::isBetween0And60InclusiveUnsigned(layer).result)
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isWinderCornerInner(Layer_ptr &layer)
{
	if (Tests::Points::Count::isEqualTo5(layer).result)
	{
		if (Tests::Interface::Angle::isBetween0And60InclusiveUnsigned(layer).result)
		{
			if (Tests::Interface::Angle::isGreaterThan0Signed(layer).result)
			{
				if (Tests::Boundary::Count::Left::isEqualTo2(layer).result)
				{
					return TestResult(true);
				}
			}
			else
			{
				if (Tests::Boundary::Count::Right::isEqualTo2(layer).result)
				{
					return TestResult(true);
				}
			}
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isWinderCornerOuter(Layer_ptr &layer)
{
	if (Tests::Points::Count::isEqualTo5(layer).result)
	{
		if (Tests::Interface::Angle::isBetween0And60InclusiveUnsigned(layer).result)
		{
			if (Tests::Interface::Angle::isGreaterThan0Signed(layer).result)
			{
				if (Tests::Boundary::Count::Right::isEqualTo2(layer).result)
				{
					return TestResult(true);
				}
			}
			else
			{
				if (Tests::Boundary::Count::Left::isEqualTo2(layer).result)
				{
					return TestResult(true);
				}
			}
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isWinderNarrow(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- Angle approximately 90deg
	 *	- At lest one boundary has only 1 edge
	 */
	if (Tests::Interface::Angle::isEqualTo90Unsigned(layer).result)
	{
		if (Tests::Boundary::Count::Left::isEqualTo1(layer).result ||
			Tests::Boundary::Count::Right::isEqualTo1(layer).result)
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isLanding90(Layer_ptr &layer)
{
	/**
	 *	Criteria:
	 *	- Angle approximately 90deg
	 *	- 5 or 6 points
	 *	- 2 edges per boundary or 1 and 2 edge boundaries
	 */
	if (Tests::Interface::Angle::isEqualTo90Unsigned(layer).result)
	{
		if (Tests::Points::Count::isEqualTo6(layer).result &&
			Tests::Boundary::Count::Left::isEqualTo2(layer).result &&
			Tests::Boundary::Count::Right::isEqualTo2(layer).result)
		{
			return TestResult(true);
		}

		if (Tests::Points::Count::isEqualTo5(layer).result &&
			((Tests::Boundary::Count::Left::isEqualTo2(layer).result &&
			Tests::Boundary::Count::Right::isEqualTo1(layer).result) ||
			(Tests::Boundary::Count::Left::isEqualTo1(layer).result &&
			Tests::Boundary::Count::Right::isEqualTo2(layer).result)))
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::Layer::isLanding180(Layer_ptr &layer)
{
	if (Tests::Interface::Angle::isEqualTo180Unsigned(layer).result)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

// Tests::Structure
TestResult Tests::Structure::hasLowerRise(Layer_ptr &layer)
{
	return TestResult(layer->lower()->getGeometry()->size() > 0);
}

TestResult Tests::Structure::hasUpperRise(Layer_ptr &layer)
{
	return TestResult(layer->upper()->getGeometry()->size() > 0);
}

TestResult Tests::Structure::hasNoLowerRise(Layer_ptr &layer)
{
	return TestResult(layer->lower()->getGeometry()->size() == 0);
}

TestResult Tests::Structure::hasNoUpperRise(Layer_ptr &layer)
{
	return TestResult(layer->upper()->getGeometry()->size() == 0);
}

// Tests::Profile
TestResult Tests::Profile::isGoingLengthWithinXpcOfRiseLength(
	Layer_ptr &layer, double pc)
{
	double g = 0, r = 0, tol, range[2];
	Rise_ptr u = layer->upper(), l = layer->lower();
	int n = 0;

	if (! u->isEmpty())
	{
		r += u->getMaxHeight() - u->getMinHeight();
		n++;
	}

	if (! l->isEmpty())
	{
		r += l->getMaxHeight() - l->getMinHeight();
		n++;
	}

	if (n == 0) return TestResult(false);

	r /= n;
	tol = r * pc;

	range[0] = r - tol;
	range[1] = r + tol;

	Edges_ptr b[2];
	b[0] = layer->left();
	b[1] = layer->right();

	if (b[0]->size() == 1)
	{
		g = b[0]->length();
	}
	else
	{
		g = b[1]->length();
	}

	return TestResult(range[0] <= g && g <= range[1]);
}

TestResult Tests::Profile::isGoingLengthWithin25pcOfRiseLength(
	Layer_ptr &layer)
{
	return (Tests::Profile::isGoingLengthWithinXpcOfRiseLength(layer,
		0.25));
}

TestResult Tests::Profile::isGoingLengthWithin50pcOfRiseLength(
	Layer_ptr &layer)
{
	return (Tests::Profile::isGoingLengthWithinXpcOfRiseLength(layer,
		0.50));
}

// Tests::Points::Count
TestResult Tests::Points::Count::isLessThanX(Layer_ptr &layer, int x)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isLessThanX(val, x);
}

TestResult Tests::Points::Count::isLessThanOrEqualToX(Layer_ptr &layer, int x)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isLessThanOrEqualToX(val, x);
}

TestResult Tests::Points::Count::isEqualToX(Layer_ptr &layer, int x)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isEqualToX(val, x);
}

TestResult Tests::Points::Count::isGreaterThanOrEqualToX(Layer_ptr &layer, int x)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isGreaterThanOrEqualToX(val, x);
}

TestResult Tests::Points::Count::isGreaterThanX(Layer_ptr &layer, int x)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isGreaterThanX(val, x);
}

TestResult Tests::Points::Count::isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isBetweenXAndY(val, x, y, incl);
}

TestResult Tests::Points::Count::isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return isBetweenXAndY(layer, x, y, true);
}

TestResult Tests::Points::Count::isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return isBetweenXAndY(layer, x, y, false);
}

TestResult Tests::Points::Count::isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	int val = Tests::Points::Helper::getCount(layer);
	return Tests::Generic::isNotBetweenXAndY(val, x, y, incl);
}

TestResult Tests::Points::Count::isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return isNotBetweenXAndY(layer, x, y, true);
}

TestResult Tests::Points::Count::isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return isNotBetweenXAndY(layer, x, y, false);
}

TestResult Tests::Points::Count::isLessThanOrEqualTo3(Layer_ptr &layer)
{
	return isLessThanOrEqualToX(layer, 3);
}

TestResult Tests::Points::Count::isEqualTo3(Layer_ptr &layer)
{
	return isEqualToX(layer, 3);
}

TestResult Tests::Points::Count::isEqualTo4(Layer_ptr &layer)
{
	return isEqualToX(layer, 4);
}

TestResult Tests::Points::Count::isEqualTo5(Layer_ptr &layer)
{
	return isEqualToX(layer, 5);
}

TestResult Tests::Points::Count::isEqualTo6(Layer_ptr &layer)
{
	return isEqualToX(layer, 6);
}

TestResult Tests::Points::Count::isGreaterThanOrEqualTo6(Layer_ptr &layer)
{
	return isGreaterThanOrEqualToX(layer, 6);
}

// Tests::Points::Helper
int Tests::Points::Helper::getCount(Layer_ptr &layer)
{
	return layer->getGeometry()->getPoints()->size();
}

double Tests::Points::Helper::getDistanceBetween(Point_ptr &p1, Point_ptr &p2)
{
	double c[3], d = 0;

	c[0] = p2->getX() - p1->getX();
	c[1] = p2->getY() - p1->getY();
	c[2] = p2->getZ() - p1->getZ();

	for (int i = 0; i < 3; i++) d += pow(c[i], 2);

	return sqrt(d);
}

// Tests::Edge::Angle
TestResult Tests::Edge::Angle::isLessThanX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isLessThanXSigned(Layer_ptr &layer, double angle)
{
	return isLessThanX(layer, angle, true);
}

TestResult Tests::Edge::Angle::isLessThanXUnsigned(Layer_ptr &layer, double angle)
{
	return isLessThanX(layer, angle, false);
}

TestResult Tests::Edge::Angle::isLessThanOrEqualToX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isLessThanOrEqualToXSigned(Layer_ptr &layer, double angle)
{
	return isLessThanOrEqualToX(layer, angle, true);
}

TestResult Tests::Edge::Angle::isLessThanOrEqualToXUnsigned(Layer_ptr &layer, double angle)
{
	return isLessThanOrEqualToX(layer, angle, false);
}

TestResult Tests::Edge::Angle::isEqualToX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isEqualToXSigned(Layer_ptr &layer, double angle)
{
	return isEqualToX(layer, angle, true);
}

TestResult Tests::Edge::Angle::isEqualToXUnsigned(Layer_ptr &layer, double angle)
{
	return isEqualToX(layer, angle, false);
}

TestResult Tests::Edge::Angle::isGreaterThanOrEqualToX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isGreaterThanOrEqualToXSigned(Layer_ptr &layer, double angle)
{
	return isGreaterThanOrEqualToX(layer, angle, true);
}

TestResult Tests::Edge::Angle::isGreaterThanOrEqualToXUnsigned(Layer_ptr &layer, double angle)
{
	return isGreaterThanOrEqualToX(layer, angle, false);
}

TestResult Tests::Edge::Angle::isGreaterThanX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isGreaterThanXSigned(Layer_ptr &layer, double angle)
{
	return isGreaterThanX(layer, angle, true);
}

TestResult Tests::Edge::Angle::isGreaterThanXUnsigned(Layer_ptr &layer, double angle)
{
	return isGreaterThanX(layer, angle, false);
}

TestResult Tests::Edge::Angle::isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isBetweenXAndY(layer, x, y, incl, true);
}

TestResult Tests::Edge::Angle::isBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isBetweenXAndY(layer, x, y, incl, false);
}

TestResult Tests::Edge::Angle::isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isBetweenXAndY(layer, x, y, true, hasSign);
}

TestResult Tests::Edge::Angle::isBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYInclusive(layer, x, y, true);
}

TestResult Tests::Edge::Angle::isBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYInclusive(layer, x, y, false);
}

TestResult Tests::Edge::Angle::isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isBetweenXAndY(layer, x, y, false, hasSign);
}

TestResult Tests::Edge::Angle::isBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYExclusive(layer, x, y, true);
}

TestResult Tests::Edge::Angle::isBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYExclusive(layer, x, y, false);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isNotBetweenXAndY(layer, x, y, incl, true);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isNotBetweenXAndY(layer, x, y, incl, false);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(layer, x, y, true, hasSign);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYInclusive(layer, x, y, true);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYInclusive(layer, x, y, false);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(layer, x, y, false, hasSign);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYExclusive(layer, x, y, true);
}

TestResult Tests::Edge::Angle::isNotBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYExclusive(layer, x, y, false);
}

// Tests::Edge::Helper
double Tests::Edge::Helper::getAngle(Edge_ptr &edge)
{
	//TODO: implement method
	return 0;
}

// Tests::Interface::Angle
TestResult Tests::Interface::Angle::isLessThanX(Layer_ptr &layer, double x, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isLessThanX(val, x, hasSign);
}

TestResult Tests::Interface::Angle::isLessThanXSigned(Layer_ptr &layer, double x)
{
	return isLessThanX(layer, x, true);
}

TestResult Tests::Interface::Angle::isLessThanXUnsigned(Layer_ptr &layer, double x)
{
	return isLessThanX(layer, x, false);
}

TestResult Tests::Interface::Angle::isLessThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isLessThanOrEqualToX(val, x, hasSign);
}

TestResult Tests::Interface::Angle::isLessThanOrEqualToXSigned(Layer_ptr &layer, double x)
{
	return isLessThanOrEqualToX(layer, x, true);
}

TestResult Tests::Interface::Angle::isLessThanOrEqualToXUnsigned(Layer_ptr &layer, double x)
{
	return isLessThanOrEqualToX(layer, x, false);
}

TestResult Tests::Interface::Angle::isEqualToX(Layer_ptr &layer, double x, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isEqualToX(val, x, hasSign);
}

TestResult Tests::Interface::Angle::isEqualToXSigned(Layer_ptr &layer, double x)
{
	return isEqualToX(layer, x, true);
}

TestResult Tests::Interface::Angle::isEqualToXUnsigned(Layer_ptr &layer, double x)
{
	return isEqualToX(layer, x, false);
}

TestResult Tests::Interface::Angle::isGreaterThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isGreaterThanOrEqualToX(val, x, hasSign);
}

TestResult Tests::Interface::Angle::isGreaterThanOrEqualToXSigned(Layer_ptr &layer, double x)
{
	return isGreaterThanOrEqualToX(layer, x, true);
}

TestResult Tests::Interface::Angle::isGreaterThanOrEqualToXUnsigned(Layer_ptr &layer, double x)
{
	return isGreaterThanOrEqualToX(layer, x, false);
}

TestResult Tests::Interface::Angle::isGreaterThanX(Layer_ptr &layer, double x, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isGreaterThanX(val, x, hasSign);
}

TestResult Tests::Interface::Angle::isGreaterThanXSigned(Layer_ptr &layer, double x)
{
	return isGreaterThanX(layer, x, true);
}

TestResult Tests::Interface::Angle::isGreaterThanXUnsigned(Layer_ptr &layer, double x)
{
	return isGreaterThanX(layer, x, false);
}

TestResult Tests::Interface::Angle::isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isBetweenXAndY(val, x, y, incl, hasSign);
}

TestResult Tests::Interface::Angle::isBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isBetweenXAndY(layer, x, y, incl, true);
}

TestResult Tests::Interface::Angle::isBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isBetweenXAndY(layer, x, y, incl, false);
}

TestResult Tests::Interface::Angle::isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isBetweenXAndY(layer, x, y, true, hasSign);
}

TestResult Tests::Interface::Angle::isBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYInclusive(layer, x, y, true);
}

TestResult Tests::Interface::Angle::isBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYInclusive(layer, x, y, false);
}

TestResult Tests::Interface::Angle::isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isBetweenXAndY(layer, x, y, false, hasSign);
}

TestResult Tests::Interface::Angle::isBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYExclusive(layer, x, y, true);
}

TestResult Tests::Interface::Angle::isBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isBetweenXAndYExclusive(layer, x, y, false);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign)
{
	double val = Tests::Interface::Helper::getAngle(layer);
	return Tests::Generic::isNotBetweenXAndY(val, x, y, incl, hasSign);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isNotBetweenXAndY(layer, x, y, incl, true);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl)
{
	return isNotBetweenXAndY(layer, x, y, incl, false);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(layer, x, y, true, hasSign);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYInclusive(layer, x, y, true);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYInclusive(layer, x, y, false);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(layer, x, y, false, hasSign);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYExclusive(layer, x, y, true);
}

TestResult Tests::Interface::Angle::isNotBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y)
{
	return isNotBetweenXAndYExclusive(layer, x, y, false);
}

TestResult Tests::Interface::Angle::isLessThan90Unsigned(Layer_ptr &layer)
{
	return isLessThanXUnsigned(layer, M_PI_2);
}

TestResult Tests::Interface::Angle::isLessThan0Signed(Layer_ptr &layer)
{
	return isLessThanXSigned(layer, 0);
}

TestResult Tests::Interface::Angle::isEqualTo0Unsigned(Layer_ptr &layer)
{
	return isEqualToXUnsigned(layer, 0);
}

TestResult Tests::Interface::Angle::isEqualTo90Unsigned(Layer_ptr &layer)
{
	return isEqualToXUnsigned(layer, M_PI / 2);
}

TestResult Tests::Interface::Angle::isEqualTo180Unsigned(Layer_ptr &layer)
{
	return isEqualToXUnsigned(layer, M_PI);
}

TestResult Tests::Interface::Angle::isGreaterThan0Signed(Layer_ptr &layer)
{
	return isGreaterThanXSigned(layer, 0);
}

TestResult Tests::Interface::Angle::isBetween0And60InclusiveUnsigned(Layer_ptr &layer)
{
	return isBetweenXAndYInclusiveUnsigned(layer, 0, M_PI / 3);
}

// Tests::Interface::Position

// Tests::Interface::Helper
double Tests::Interface::Helper::getAngle(Layer_ptr &layer)
{
	return layer->getIfcAngle();
}

// Tests::Boundary::Count::Generic
TestResult Tests::Boundary::Count::Generic::isLessThanX(Edges_ptr &edges, int x)
{
	int val = edges->size();
	return Tests::Generic::isLessThanX(val, x);
}

TestResult Tests::Boundary::Count::Generic::isLessThanOrEqualToX(Edges_ptr &edges, int x)
{
	int val = edges->size();
	return Tests::Generic::isLessThanOrEqualToX(val, x);
}

TestResult Tests::Boundary::Count::Generic::isEqualToX(Edges_ptr &edges, int x)
{
	int val = edges->size();
	return Tests::Generic::isEqualToX(val, x);
}

TestResult Tests::Boundary::Count::Generic::isGreaterThanOrEqualToX(Edges_ptr &edges, int x)
{
	int val = edges->size();
	return Tests::Generic::isGreaterThanOrEqualToX(val, x);
}

TestResult Tests::Boundary::Count::Generic::isGreaterThanX(Edges_ptr &edges, int x)
{
	int val = edges->size();
	return Tests::Generic::isGreaterThanX(val, x);
}

TestResult Tests::Boundary::Count::Generic::isBetweenXAndY(Edges_ptr &edges, int x, int y, bool incl)
{
	int val = edges->size();
	return Tests::Generic::isBetweenXAndY(val, x, y, incl);
}

TestResult Tests::Boundary::Count::Generic::isBetweenXAndYInclusive(Edges_ptr &edges, int x, int y)
{
	return isBetweenXAndY(edges, x, y, true);
}

TestResult Tests::Boundary::Count::Generic::isBetweenXAndYExclusive(Edges_ptr &edges, int x, int y)
{
	return isBetweenXAndY(edges, x, y, false);
}

TestResult Tests::Boundary::Count::Generic::isNotBetweenXAndY(Edges_ptr &edges, int x, int y, bool incl)
{
	int val = edges->size();
	return Tests::Generic::isNotBetweenXAndY(val, x, y, incl);
}

TestResult Tests::Boundary::Count::Generic::isNotBetweenXAndYInclusive(Edges_ptr &edges, int x, int y)
{
	return isNotBetweenXAndY(edges, x, y, true);
}

TestResult Tests::Boundary::Count::Generic::isNotBetweenXAndYExclusive(Edges_ptr &edges, int x, int y)
{
	return isNotBetweenXAndY(edges, x, y, false);
}

TestResult Tests::Boundary::Count::Generic::isEqualTo1(Edges_ptr &edges)
{
	return isEqualToX(edges, 1);
}

TestResult Tests::Boundary::Count::Generic::isEqualTo2(Edges_ptr &edges)
{
	return isEqualToX(edges, 2);
}

TestResult Tests::Boundary::Count::Generic::isEqualTo3(Edges_ptr &edges)
{
	return isEqualToX(edges, 3);
}

// Tests::Boundary::Count::Left
TestResult Tests::Boundary::Count::Left::isLessThanX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isLessThanX(layer->left(), x);
}

TestResult Tests::Boundary::Count::Left::isLessThanOrEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isLessThanOrEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Count::Left::isEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Count::Left::isGreaterThanOrEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isGreaterThanOrEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Count::Left::isGreaterThanX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isGreaterThanX(layer->left(), x);
}

TestResult Tests::Boundary::Count::Left::isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndY(layer->left(), x, y, incl);
}

TestResult Tests::Boundary::Count::Left::isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndYInclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Count::Left::isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndYExclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Count::Left::isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndY(layer->left(), x, y, incl);
}

TestResult Tests::Boundary::Count::Left::isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndYInclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Count::Left::isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndYExclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Count::Left::isEqualTo1(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo1(layer->left());
}

TestResult Tests::Boundary::Count::Left::isEqualTo2(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo2(layer->left());
}

TestResult Tests::Boundary::Count::Left::isEqualTo3(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo3(layer->left());
}

// Tests::Boundary::Count::Right
TestResult Tests::Boundary::Count::Right::isLessThanX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isLessThanX(layer->right(), x);
}

TestResult Tests::Boundary::Count::Right::isLessThanOrEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isLessThanOrEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Count::Right::isEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Count::Right::isGreaterThanOrEqualToX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isGreaterThanOrEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Count::Right::isGreaterThanX(Layer_ptr &layer, int x)
{
	return Tests::Boundary::Count::Generic::isGreaterThanX(layer->right(), x);
}

TestResult Tests::Boundary::Count::Right::isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndY(layer->right(), x, y, incl);
}

TestResult Tests::Boundary::Count::Right::isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndYInclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Count::Right::isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isBetweenXAndYExclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Count::Right::isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndY(layer->right(), x, y, incl);
}

TestResult Tests::Boundary::Count::Right::isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndYInclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Count::Right::isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return Tests::Boundary::Count::Generic::isNotBetweenXAndYExclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Count::Right::isEqualTo1(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo1(layer->right());
}

TestResult Tests::Boundary::Count::Right::isEqualTo2(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo2(layer->right());
}

TestResult Tests::Boundary::Count::Right::isEqualTo3(Layer_ptr &layer)
{
	return Tests::Boundary::Count::Generic::isEqualTo3(layer->right());
}

// Tests::Boundary::Length::Generic
TestResult Tests::Boundary::Length::Generic::isLessThanX(Edges_ptr &edges, double x)
{
	double val = edges->length();
	return Tests::Generic::isLessThanX(val, x, false);
}

TestResult Tests::Boundary::Length::Generic::isLessThanOrEqualToX(Edges_ptr &edges, double x)
{
	double val = edges->length();
	return Tests::Generic::isLessThanOrEqualToX(val, x, false);
}

TestResult Tests::Boundary::Length::Generic::isEqualToX(Edges_ptr &edges, double x)
{
	double val = edges->length();
	return Tests::Generic::isEqualToX(val, x, false);
}

TestResult Tests::Boundary::Length::Generic::isGreaterThanOrEqualToX(Edges_ptr &edges, double x)
{
	double val = edges->length();
	return Tests::Generic::isGreaterThanOrEqualToX(val, x, false);
}

TestResult Tests::Boundary::Length::Generic::isGreaterThanX(Edges_ptr &edges, double x)
{
	double val = edges->length();
	return Tests::Generic::isGreaterThanX(val, x, false);
}

TestResult Tests::Boundary::Length::Generic::isBetweenXAndY(Edges_ptr &edges, double x, double y, bool incl)
{
	double val = edges->length();
	return Tests::Generic::isBetweenXAndY(val, x, y, incl, false);
}

TestResult Tests::Boundary::Length::Generic::isBetweenXAndYInclusive(Edges_ptr &edges, double x, double y)
{
	return isBetweenXAndY(edges, x, y, true);
}

TestResult Tests::Boundary::Length::Generic::isBetweenXAndYExclusive(Edges_ptr &edges, double x, double y)
{
	return isBetweenXAndY(edges, x, y, false);
}

TestResult Tests::Boundary::Length::Generic::isNotBetweenXAndY(Edges_ptr &edges, double x, double y, bool incl)
{
	double val = edges->length();
	return Tests::Generic::isNotBetweenXAndY(val, x, y, incl, false);
}

TestResult Tests::Boundary::Length::Generic::isNotBetweenXAndYInclusive(Edges_ptr &edges, double x, double y)
{
	return isNotBetweenXAndY(edges, x, y, true);
}

TestResult Tests::Boundary::Length::Generic::isNotBetweenXAndYExclusive(Edges_ptr &edges, double x, double y)
{
	return isNotBetweenXAndY(edges, x, y, false);
}

// Tests::Boundary::Length::Left
TestResult Tests::Boundary::Length::Left::isLessThanX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isLessThanX(layer->left(), x);
}

TestResult Tests::Boundary::Length::Left::isLessThanOrEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isLessThanOrEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Length::Left::isEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Length::Left::isGreaterThanOrEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isGreaterThanOrEqualToX(layer->left(), x);
}

TestResult Tests::Boundary::Length::Left::isGreaterThanX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isGreaterThanX(layer->left(), x);
}

TestResult Tests::Boundary::Length::Left::isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndY(layer->left(), x, y, incl);
}

TestResult Tests::Boundary::Length::Left::isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndYInclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Length::Left::isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndYExclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Length::Left::isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndY(layer->left(), x, y, incl);
}

TestResult Tests::Boundary::Length::Left::isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndYInclusive(layer->left(), x, y);
}

TestResult Tests::Boundary::Length::Left::isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndYExclusive(layer->left(), x, y);
}

// Tests::Boundary::Length::Right
TestResult Tests::Boundary::Length::Right::isLessThanX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isLessThanX(layer->right(), x);
}

TestResult Tests::Boundary::Length::Right::isLessThanOrEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isLessThanOrEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Length::Right::isEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Length::Right::isGreaterThanOrEqualToX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isGreaterThanOrEqualToX(layer->right(), x);
}

TestResult Tests::Boundary::Length::Right::isGreaterThanX(Layer_ptr &layer, double x)
{
	return Tests::Boundary::Length::Generic::isGreaterThanX(layer->right(), x);
}

TestResult Tests::Boundary::Length::Right::isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndY(layer->right(), x, y, incl);
}

TestResult Tests::Boundary::Length::Right::isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndYInclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Length::Right::isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isBetweenXAndYExclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Length::Right::isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndY(layer->right(), x, y, incl);
}

TestResult Tests::Boundary::Length::Right::isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndYInclusive(layer->right(), x, y);
}

TestResult Tests::Boundary::Length::Right::isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return Tests::Boundary::Length::Generic::isNotBetweenXAndYExclusive(layer->right(), x, y);
}

// Tests::Boundary::Helper
void Tests::Boundary::Helper::getLengths(double* arr, Layer_ptr &layer)
{
	arr[0] = getLeftLength(layer);
	arr[1] = getRightLength(layer);
}

double Tests::Boundary::Helper::getLeftLength(Layer_ptr &layer)
{
	return layer->left()->length();
}

double Tests::Boundary::Helper::getRightLength(Layer_ptr &layer)
{
	return layer->right()->length();
}

void Tests::Boundary::Helper::getCounts(int* arr, Layer_ptr &layer)
{
	arr[0] = getLeftCount(layer);
	arr[1] = getRightCount(layer);
}

int Tests::Boundary::Helper::getLeftCount(Layer_ptr &layer)
{
	return layer->left()->size();
}

int Tests::Boundary::Helper::getRightCount(Layer_ptr &layer)
{
	return layer->right()->size();
}

// Tests::Generic
TestResult Tests::Generic::isLessThanX(int val, int x)
{
	return TestResult(val < x);
}

TestResult Tests::Generic::isLessThanOrEqualToX(int val, int x)
{
	return TestResult(val <= x);
}

TestResult Tests::Generic::isEqualToX(int val, int x)
{
	return TestResult(val == x);
}

TestResult Tests::Generic::isGreaterThanOrEqualToX(int val, int x)
{
	return TestResult(val >= x);
}

TestResult Tests::Generic::isGreaterThanX(int val, int x)
{
	return TestResult(val > x);
}

TestResult Tests::Generic::isBetweenXAndY(int val, int x, int y, bool incl)
{
	if (incl)
	{
		x--;
		y++;
	}

	return TestResult(val > x && val < y);
}

TestResult Tests::Generic::isBetweenXAndYInclusive(int val, int x, int y)
{
	return isBetweenXAndY(val, x, y, true);
}

TestResult Tests::Generic::isBetweenXAndYExclusive(int val, int x, int y)
{
	return isBetweenXAndY(val, x, y, false);
}

TestResult Tests::Generic::isNotBetweenXAndY(int val, int x, int y, bool incl)
{
	if (incl)
	{
		x++;
		y--;
	}

	return TestResult(val < x && val > y);
}

TestResult Tests::Generic::isNotBetweenXAndYInclusive(int val, int x, int y)
{
	return isNotBetweenXAndY(val, x, y, true);
}

TestResult Tests::Generic::isNotBetweenXAndYExclusive(int val, int x, int y)
{
	return isNotBetweenXAndY(val, x, y, false);
}

TestResult Tests::Generic::isLessThanX(double val, double x, bool hasSign)
{
	return TestResult(val < x || (val * -1) < x);
}

TestResult Tests::Generic::isLessThanXSigned(double val, double x)
{
	return isLessThanX(val, x, true);
}

TestResult Tests::Generic::isLessThanXUnsigned(double val, double x)
{
	return isLessThanX(val, x, false);
}

TestResult Tests::Generic::isLessThanOrEqualToX(double val, double x, bool hasSign)
{
	return TestResult(val <= x || (val * -1) <= x);
}

TestResult Tests::Generic::isLessThanOrEqualToXSigned(double val, double x)
{
	return isLessThanOrEqualToX(val, x, true);
}

TestResult Tests::Generic::isLessThanOrEqualToXUnsigned(double val, double x)
{
	return isLessThanOrEqualToX(val, x, false);
}

TestResult Tests::Generic::isEqualToX(double val, double x, bool hasSign)
{
	double range[2];
	Tests::Helper::getRange(range, x, angTol);

	if (val > range[0] && val < range[1])
	{
		return TestResult(true);
	}

	if (! hasSign)
	{
		val *= -1;
		return isEqualToX(val, x, true);
	}

	return TestResult(false);
}

TestResult Tests::Generic::isEqualToXSigned(double val, double x)
{
	return isEqualToX(val, x, true);
}

TestResult Tests::Generic::isEqualToXUnsigned(double val, double x)
{
	return isEqualToX(val, x, false);
}

TestResult Tests::Generic::isGreaterThanOrEqualToX(double val, double x, bool hasSign)
{
	return TestResult(val >= x);
}

TestResult Tests::Generic::isGreaterThanOrEqualToXSigned(double val, double x)
{
	return isGreaterThanOrEqualToX(val, x, true);
}

TestResult Tests::Generic::isGreaterThanOrEqualToXUnsigned(double val, double x)
{
	return isGreaterThanOrEqualToX(val, x, false);
}

TestResult Tests::Generic::isGreaterThanX(double val, double x, bool hasSign)
{
	return TestResult(val > x);
}

TestResult Tests::Generic::isGreaterThanXSigned(double val, double x)
{
	return isGreaterThanX(val, x, true);
}

TestResult Tests::Generic::isGreaterThanXUnsigned(double val, double x)
{
	return isGreaterThanX(val, x, false);
}

TestResult Tests::Generic::isBetweenXAndY(double val, double x, double y, bool incl, bool hasSign)
{
	if (val > x && val < y)
	{
		return TestResult(true);
	}

	if (incl)
	{
		if (val >= x && val <= y)
		{
			return TestResult(true);
		}
	}

	if (! hasSign)
	{
		val *= -1;
		return isBetweenXAndY(val, x, y, false, true);
	}

	return TestResult(false);
}

TestResult Tests::Generic::isBetweenXAndYSigned(double val, double x, double y, bool incl)
{
	return isBetweenXAndY(val, x, y, incl, true);
}

TestResult Tests::Generic::isBetweenXAndYUnsigned(double val, double x, double y, bool incl)
{
	return isBetweenXAndY(val, x, y, incl, false);
}

TestResult Tests::Generic::isBetweenXAndYInclusive(double val, double x, double y, bool hasSign)
{
	return isBetweenXAndY(val, x, y, true, hasSign);
}

TestResult Tests::Generic::isBetweenXAndYInclusiveSigned(double val, double x, double y)
{
	return isBetweenXAndYInclusive(val, x, y, true);
}

TestResult Tests::Generic::isBetweenXAndYInclusiveUnsigned(double val, double x, double y)
{
	return isBetweenXAndYInclusive(val, x, y, false);
}

TestResult Tests::Generic::isBetweenXAndYExclusive(double val, double x, double y, bool hasSign)
{
	return isBetweenXAndY(val, x, y, false, hasSign);
}

TestResult Tests::Generic::isBetweenXAndYExclusiveSigned(double val, double x, double y)
{
	return isBetweenXAndYExclusive(val, x, y, true);
}

TestResult Tests::Generic::isBetweenXAndYExclusiveUnsigned(double val, double x, double y)
{
	return isBetweenXAndYExclusive(val, x, y, false);
}

TestResult Tests::Generic::isNotBetweenXAndY(double val, double x, double y, bool incl, bool hasSign)
{
	if (val < x && val > y)
	{
		return TestResult(true);
	}

	if (incl)
	{
		if (val <= x && val >= y)
		{
			return TestResult(true);
		}
	}

	if (! hasSign)
	{
		val *= -1;
		return isNotBetweenXAndY(val, x, y, false, true);
	}

	return TestResult(false);
}

TestResult Tests::Generic::isNotBetweenXAndYSigned(double val, double x, double y, bool incl)
{
	return isNotBetweenXAndY(val, x, y, incl, true);
}

TestResult Tests::Generic::isNotBetweenXAndYUnsigned(double val, double x, double y, bool incl)
{
	return isNotBetweenXAndY(val, x, y, incl, false);
}

TestResult Tests::Generic::isNotBetweenXAndYInclusive(double val, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(val, x, y, true, hasSign);
}

TestResult Tests::Generic::isNotBetweenXAndYInclusiveSigned(double val, double x, double y)
{
	return isNotBetweenXAndYInclusive(val, x, y, true);
}

TestResult Tests::Generic::isNotBetweenXAndYInclusiveUnsigned(double val, double x, double y)
{
	return isNotBetweenXAndYInclusive(val, x, y, false);
}

TestResult Tests::Generic::isNotBetweenXAndYExclusive(double val, double x, double y, bool hasSign)
{
	return isNotBetweenXAndY(val, x, y, false, hasSign);
}

TestResult Tests::Generic::isNotBetweenXAndYExclusiveSigned(double val, double x, double y)
{
	return isNotBetweenXAndYExclusive(val, x, y, true);
}

TestResult Tests::Generic::isNotBetweenXAndYExclusiveUnsigned(double val, double x, double y)
{
	return isNotBetweenXAndYExclusive(val, x, y, false);
}

// Tests::Helper
void Tests::Helper::getRange(double* range, double val, double tol)
{
	range[0] = val - tol;
	range[1] = val + tol;
}

void Tests::Helper::getRange(double* range, double val1, double val2,
						  double tol)
{
	range[0] = val1 - tol;
	range[1] = val2 + tol;
}