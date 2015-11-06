#ifndef TEST_H
#define TEST_H

#include "layer.h"
#include "tester.h"

namespace Tests
{
	TestResult HasLayerGotXPoints(Layer_ptr layer, int count);
	TestResult HasLayerGotXOrMorePoints(Layer_ptr layer, int count);
	TestResult HasLayerGotFourPoints(Layer_ptr layer);
	TestResult HasLayerGotFivePoints(Layer_ptr layer);
	TestResult HasLayerGotSixOrMorePoints(Layer_ptr layer);
	TestResult AreTheInterfacesParallel(Layer_ptr layer);
};

#endif