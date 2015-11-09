#ifndef TEST_H
#define TEST_H

#include "layer.h"
#include "tester.h"

namespace Tests
{
	// Points - non-specific
	TestResult isPointCountLessThanX(Layer_ptr layer, int count);
	TestResult isPointCountLessThanOrEqualToX(Layer_ptr layer, int count);
	TestResult isPointCountEqualToX(Layer_ptr layer, int count);
	TestResult isPointCountGreaterThanOrEqualToX(Layer_ptr layer, int count);
	TestResult isPointCountGreaterThanX(Layer_ptr layer, int count);
	TestResult isPointCountBetweenXAndY(Layer_ptr layer, int x, int y, bool inclusive);
	TestResult isPointCountBetweenXAndYInclusive(Layer_ptr layer, int x, int y);
	TestResult isPointCountBetweenXAndYExclusive(Layer_ptr layer, int x, int y);
	TestResult isPointCountNotBetweenXAndY(Layer_ptr layer, int x, int y, bool inclusive);
	TestResult isPointCountNotBetweenXAndYInclusive(Layer_ptr layer, int x, int y);
	TestResult isPointCountNotBetweenXAndYExclusive(Layer_ptr layer, int x, int y);

	// Points - specific
	TestResult isPointCountLessThanOrEqualTo3(Layer_ptr layer);
	TestResult isPointCountEqualTo4(Layer_ptr layer);
	TestResult isPointCountEqualTo5(Layer_ptr layer);
	TestResult isPointCountGreaterThanOrEqualTo6(Layer_ptr layer);

	// Interface Angles - non-specific
	TestResult isInterfaceAngleLessThanX(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleLessThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleEqualToX(Layer_ptr layer, double angle, bool hasSign);
	TestResult isInterfaceAngleEqualToXSigned(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleEqualToXUnsigned(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleGreaterThanX(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleGreaterThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult isInterfaceAngleBetweenXAndY(Layer_ptr layer, double x, double y, bool inclusive);
	TestResult isInterfaceAngleBetweenXAndYInclusive(Layer_ptr layer, double x, double y);
	TestResult isInterfaceAngleBetweenXAndYExclusive(Layer_ptr layer, double x, double y);
	TestResult isInterfaceAngleNotBetweenXAndY(Layer_ptr layer, double x, double y, bool inclusive);
	TestResult isInterfaceAngleNotBetweenXAndYInclusive(Layer_ptr layer, double x, double y);
	TestResult isInterfaceAngleNotBetweenXAndYExclusive(Layer_ptr layer, double x, double y);

	// Interface Angles - specific
	TestResult isInterfaceAngleLessThan90(Layer_ptr layer);
	TestResult isInterfaceAngleLessThan0(Layer_ptr layer);
	TestResult isInterfaceAngleEqualTo0(Layer_ptr layer);
	TestResult isInterfaceAngleEqualTo180(Layer_ptr layer);
	TestResult isInterfaceAngleGreaterThan0(Layer_ptr layer);
	TestResult isInterfaceAngleBetweenN60And60Inclusive(Layer_ptr layer);

	// Splitting - non-specifc
	// ..

	// Splitting - specific
	// ..

	// Edge Angles - non-specific
	TestResult isEdgeAngleLessThanX(Layer_ptr layer, double angle);
	TestResult isEdgeAngleLessThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult isEdgeAngleEqualToX(Layer_ptr layer, double angle, bool hasSign);
	TestResult isEdgeAngleEqualToXSigned(Layer_ptr layer, double angle);
	TestResult isEdgeAngleEqualToXUnsigned(Layer_ptr layer, double angle);
	TestResult isEdgeAngleGreaterThanX(Layer_ptr layer, double angle);
	TestResult isEdgeAngleGreaterThanOrEqualToX(Layer_ptr layer, double angle);
	TestResult isEdgeAngleBetweenXAndY(Layer_ptr layer, double x, double y, bool inclusive);
	TestResult isEdgeAngleBetweenXAndYInclusive(Layer_ptr layer, double x, double y);
	TestResult isEdgeAngleBetweenXAndYExclusive(Layer_ptr layer, double x, double y);
	TestResult isEdgeAngleNotBetweenXAndY(Layer_ptr layer, double x, double y, bool inclusive);
	TestResult isEdgeAngleNotBetweenXAndYInclusive(Layer_ptr layer, double x, double y);
	TestResult isEdgeAngleNotBetweenXAndYExclusive(Layer_ptr layer, double x, double y);

	// Interface Positions - non-specific
	// ..

	// Interface Positions - non-specfic
	// ..
};

namespace TestHelper
{
	int		getPointCount(Layer_ptr layer);
	double	getInterfaceAngle(Layer_ptr layer);
	void	getRange(double* range, double val, double tol);
	void	getRange(double* range, double val1, double val2, double tol);
};

#endif