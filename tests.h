#ifndef TEST_H
#define TEST_H

#include "layer.h"
#include "tester.h"

namespace Tests
{
	// Points
	TestResult HasLayerGotXPoints(Layer_ptr layer, int count);
	TestResult HasLayerGotXOrMorePoints(Layer_ptr layer, int count);
	TestResult HasLayerGotFourPoints(Layer_ptr layer);
	TestResult HasLayerGotFivePoints(Layer_ptr layer);
	TestResult HasLayerGotSixOrMorePoints(Layer_ptr layer);

	// Interface Angles
	TestResult HasInterfaceAngleEqualToX(Layer_ptr layer, double angle);
	TestResult HasInterfaceAngleLessThanX(Layer_ptr layer, double angle);
	TestResult HasInterfaceAngleLessThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult HasInterfaceAngleLessThanOrEqualTo90(Layer_ptr layer);
	TestResult HasInterfaceAngleGreaterThanX(Layer_ptr layer, double angle);
	TestResult HasInterfaceAngleGreaterThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult HasInterfaceAngleBetweenXAndY(Layer_ptr layer, double angle1, double angle2);

	TestResult HasInterfaceAngleEqualTo0(Layer_ptr layer);
	TestResult HasInterfaceAngleEqualTo180(Layer_ptr layer);
	TestResult HasInterfaceAngleLessThan90(Layer_ptr layer);

	// Splitting
	// ..

	// Edge Angles
	// ..

	// Interface Position
	// ..

};

namespace TestsHelpers
{

};

#endif