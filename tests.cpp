using namespace std;

#define _USE_MATH_DEFINES

#include "tests.h"
#include <math.h>

const double angTol = 5 * M_PI / 180;	// 5 degrees

TestResult Tests::isPointCountLessThanX(Layer_ptr &layer, int count)
{
	if (TestHelper::getPointCount(layer) < count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountLessThanOrEqualToX(Layer_ptr &layer, int count)
{
	if (TestHelper::getPointCount(layer) <= count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountEqualToX(Layer_ptr &layer, int count)
{
	if (TestHelper::getPointCount(layer) == count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountGreaterThanOrEqualToX(Layer_ptr &layer, int count)
{
	if (TestHelper::getPointCount(layer) >= count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountGreaterThanX(Layer_ptr &layer, int count)
{
	if (TestHelper::getPointCount(layer) > count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountBetweenXAndY(Layer_ptr &layer, int x, int y, bool inclusive)
{
	int count = TestHelper::getPointCount(layer);
	if (inclusive)
	{
		x--;
		y++;
	}

	if (count > x && count < y)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isPointCountBetweenXAndYInclusive(Layer_ptr &layer, int x, int y)
{
	return isPointCountBetweenXAndY(layer, x, y, true);
}

TestResult Tests::isPointCountBetweenXAndYExclusive(Layer_ptr &layer, int x, int y)
{
	return isPointCountBetweenXAndY(layer, x, y, false);
}

TestResult Tests::isPointCountLessThanOrEqualTo3(Layer_ptr &layer)
{
	return isPointCountLessThanOrEqualToX(layer, 3);
}

TestResult Tests::isPointCountEqualTo4(Layer_ptr &layer)
{
	return isPointCountEqualToX(layer, 4);
}

TestResult Tests::isPointCountEqualTo5(Layer_ptr &layer)
{
	return isPointCountEqualToX(layer, 5);
}

TestResult Tests::isPointCountGreaterThanOrEqualTo6(Layer_ptr &layer)
{
	return isPointCountGreaterThanOrEqualToX(layer, 6);
}

TestResult Tests::isInterfaceAngleLessThanX(Layer_ptr &layer, double angle)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (ifcAngle < angle)
	{
		return TestResult(true);
	}
	return TestResult(false);
}

TestResult Tests::isInterfaceAngleLessThanOrEqualToX(Layer_ptr &layer, double angle)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (ifcAngle <= angle)
	{
		return TestResult(true);
	}
	return TestResult(false);
}

TestResult Tests::isInterfaceAngleEqualToX(Layer_ptr &layer, double angle, bool hasSign)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	double range[2];
	TestHelper::getRange(range, angle, angTol);

	if ((ifcAngle > range[0] && ifcAngle < range[1]) ||
		((-1 * ifcAngle) > range[0] && (-1 * ifcAngle) < range[1]))
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::isInterfaceAngleEqualToXSigned(Layer_ptr &layer, double angle)
{
	return isInterfaceAngleEqualToX(layer, angle, true);
}

TestResult Tests::isInterfaceAngleEqualToXUnsigned(Layer_ptr &layer, double angle)
{
	return isInterfaceAngleEqualToX(layer, angle, false);
}

TestResult Tests::isInterfaceAngleGreaterThanOrEqualToX(Layer_ptr &layer, double angle)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (ifcAngle >= angle)
	{
		return TestResult(true);
	}
	return TestResult(false);
}

TestResult Tests::isInterfaceAngleGreaterThanX(Layer_ptr &layer, double angle)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (ifcAngle > angle)
	{
		return TestResult(true);
	}
	return TestResult(false);
}

TestResult Tests::isInterfaceAngleBetweenXAndY(Layer_ptr &layer, double x, double y, bool inclusive)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (inclusive)
	{
		if (ifcAngle >= x && ifcAngle <= y)
		{
			return TestResult(true);
		}
	}
	else
	{
		if (ifcAngle > x && ifcAngle < y)
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::isInterfaceAngleBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return isInterfaceAngleBetweenXAndY(layer, x, y, true);
}

TestResult Tests::isInterfaceAngleBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return isInterfaceAngleBetweenXAndY(layer, x, y, false);
}

TestResult Tests::isInterfaceAngleNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool inclusive)
{
	double ifcAngle = TestHelper::getInterfaceAngle(layer);
	
	if (inclusive)
	{
		if (ifcAngle <= x && ifcAngle >= y)
		{
			return TestResult(true);
		}
	}
	else
	{
		if (ifcAngle < x && ifcAngle > y)
		{
			return TestResult(true);
		}
	}

	return TestResult(false);
}

TestResult Tests::isInterfaceAngleNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return isInterfaceAngleNotBetweenXAndY(layer, x, y, true);
}

TestResult Tests::isInterfaceAngleNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return isInterfaceAngleNotBetweenXAndY(layer, x, y, false);
}

TestResult Tests::isInterfaceAngleLessThan90(Layer_ptr &layer)
{
	return isInterfaceAngleLessThanX(layer, M_PI_2);
}

TestResult Tests::isInterfaceAngleLessThan0(Layer_ptr &layer)
{
	return isInterfaceAngleLessThanX(layer, 0);
}

TestResult Tests::isInterfaceAngleEqualTo0(Layer_ptr &layer)
{
	return isInterfaceAngleEqualToXSigned(layer, 0);
}

TestResult Tests::isInterfaceAngleEqualTo90Unsigned(Layer_ptr &layer)
{
	return isInterfaceAngleEqualToXUnsigned(layer, M_PI / 2);
}

TestResult Tests::isInterfaceAngleEqualTo180(Layer_ptr &layer)
{
	return isInterfaceAngleEqualToXUnsigned(layer, M_PI);
}

TestResult Tests::isInterfaceAngleGreaterThan0(Layer_ptr &layer)
{
	return isInterfaceAngleGreaterThanX(layer, 0);
}

TestResult Tests::isInterfaceAngleBetweenN60And60Inclusive(Layer_ptr &layer)
{
	return isInterfaceAngleBetweenXAndYInclusive(layer, -1 * (M_PI / 3), M_PI / 3);
}

TestResult Tests::isEdgeAngleLessThanX(Layer_ptr &layer, double angle)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleLessThanOrEqualToX(Layer_ptr &layer, double angle)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleEqualToX(Layer_ptr &layer, double angle, bool hasSign)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleEqualToXSigned(Layer_ptr &layer, double angle)
{
	return isEdgeAngleEqualToX(layer, angle, true);
}

TestResult Tests::isEdgeAngleEqualToXUnsigned(Layer_ptr &layer, double angle)
{
	return isEdgeAngleEqualToX(layer, angle, false);
}

TestResult Tests::isEdgeAngleGreaterThanX(Layer_ptr &layer, double angle)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleGreaterThanOrEqualToX(Layer_ptr &layer, double angle)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleBetweenXAndY(Layer_ptr &layer, double x, double y, bool inclusive)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return isEdgeAngleBetweenXAndY(layer, x, y, true);
}

TestResult Tests::isEdgeAngleBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return isEdgeAngleBetweenXAndY(layer, x, y, false);
}

TestResult Tests::isEdgeAngleNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool inclusive)
{
	//TODO: implement method
	return TestResult(true);
}

TestResult Tests::isEdgeAngleNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y)
{
	return isEdgeAngleNotBetweenXAndY(layer, x, y, true);
}

TestResult Tests::isEdgeAngleNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y)
{
	return isEdgeAngleNotBetweenXAndY(layer, x, y, false);
}

int TestHelper::getPointCount(Layer_ptr &layer)
{
	return layer->getGeometry()->getPoints()->size();
}

double TestHelper::getInterfaceAngle(Layer_ptr &layer)
{
	return layer->getIfcAngle();
}

void TestHelper::getRange(double* range, double val, double tol)
{
	range[0] = val - tol;
	range[1] = val + tol;
}

void TestHelper::getRange(double* range, double val1, double val2, double tol)
{
	range[0] = val1 - tol;
	range[1] = val2 + tol;
}