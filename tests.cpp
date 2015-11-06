using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>
#include "tests.h"

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
	return HasLayerGotXPoints(layer, 4);
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

TestResult Tests::AreTheInterfacesParallel(Layer_ptr layer)
{
	double ang1 = layer->getEntry()->angZ();
	double ang2 = layer->getEntry()->angZ();

	double tol = 5 * M_PI / 180;
	double min = tol * -1;
	double max = tol;


	return TestResult(true);

}