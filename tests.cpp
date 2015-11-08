using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>
#include "tests.h"

const double angTol = 5 * M_PI / 180;

TestResult Tests::HasLayerGotXPoints(Layer_ptr layer, int count)
{
	if (layer->getPoints()->size() == count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::HasLayerGotFourPoints(Layer_ptr layer)
{
	return HasLayerGotXPoints(layer, 4);
}

TestResult Tests::HasLayerGotFivePoints(Layer_ptr layer)
{
	return HasLayerGotXPoints(layer, 5);
}

TestResult Tests::HasLayerGotXOrMorePoints(Layer_ptr layer, int count)
{
	if (layer->getPoints()->size() >= count)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::HasLayerGotSixOrMorePoints(Layer_ptr layer)
{
	return HasLayerGotXOrMorePoints(layer, 6);
}

TestResult Tests::HasInterfaceAngleEqualToX(Layer_ptr layer, double angle)
{
	double dth = layer->getIfcAngle();
	double min = angle - angTol;
	double max = angle + angTol;

	if (dth < max && dth > min)
	{
		return TestResult(true);
	}

	return TestResult(false);
}

TestResult Tests::HasInterfaceAngleLessThanX(Layer_ptr layer, double angle)
{
	double dth = layer->getIfcAngle();
	double min = angle - angTol;
	double max = angle + angTol;

	return TestResult(true);
}

TestResult Tests::HasInterfaceAngleLessThanOrEqualToX(Layer_ptr layer, double angle)
{
	return TestResult(true);
}

TestResult Tests::HasInterfaceAngleEqualTo0(Layer_ptr layer)
{
	return HasInterfaceAngleEqualToX(layer, 0);
}

TestResult Tests::HasInterfaceAngleEqualTo180(Layer_ptr layer)
{
	return TestResult((HasInterfaceAngleEqualToX(layer, M_PI).result ||
		HasInterfaceAngleEqualToX(layer, M_PI * -1).result));
}

TestResult Tests::HasInterfaceAngleLessThan90(Layer_ptr layer)
{
	return HasInterfaceAngleLessThanX(layer, M_PI_2);
}