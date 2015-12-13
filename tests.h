#ifndef TEST_H
#define TEST_H

/**
 *	tests.h
 *	---------------------------------------------------------------------------
 *	Contains the "Tests" namespace which in turn contains sub-namespaces
 *	and methods for testing for certain properties of layers.
 */

using namespace std;

#include "layer.h"
#include "edges.h"
#include "edge.h"
#include "tester.h"

/**
 *	Tests are broken down into the following major categories:
 *		- Layer
 *		- Structure
 *		- Profile
 *		- Point
 *		- Points
 *		- Edge
 *		- Edges
 *		- Facet
 *		- Facets
 *		- Interface
 *		- Boundary
 *		- Surface
 *		- Feature
 */

namespace Tests
{
	namespace Layer
	{
		TestResult isStart(Layer_ptr &layer);
		TestResult isEnd(Layer_ptr &layer);
		TestResult isStraightStandard(Layer_ptr &layer);
		TestResult isStraightExtended(Layer_ptr &layer);
		TestResult isWinderStandard(Layer_ptr &layer);
		TestResult isWinderCornerInner(Layer_ptr &layer);
		TestResult isWinderCornerOuter(Layer_ptr &layer);
		TestResult isWinderNarrow(Layer_ptr &layer);
		TestResult isLanding90(Layer_ptr &layer);
		TestResult isLanding180(Layer_ptr &layer);
	}

	namespace Structure
	{
		TestResult hasLowerRise(Layer_ptr &layer);
		TestResult hasUpperRise(Layer_ptr &layer);
		TestResult hasNoLowerRise(Layer_ptr &layer);
		TestResult hasNoUpperRise(Layer_ptr &layer);
	};

	namespace Profile
	{
		// Non-specific
		TestResult isGoingLengthWithinXpcOfRiseLength(Layer_ptr &layer,
			double pc);

		// Specific
		TestResult isGoingLengthWithin25pcOfRiseLength(Layer_ptr &layer);
		TestResult isGoingLengthWithin50pcOfRiseLength(Layer_ptr &layer);
	};

	namespace Point
	{
		namespace Helper
		{

		};
	};

	namespace Points
	{
		namespace Count
		{
			// Non-specific
			TestResult isLessThanX(Layer_ptr &layer, int x);
			TestResult isLessThanOrEqualToX(Layer_ptr &layer, int x);
			TestResult isEqualToX(Layer_ptr &layer, int x);
			TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, int x);
			TestResult isGreaterThanX(Layer_ptr &layer, int x);
			TestResult isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
			TestResult isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
			TestResult isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);
			TestResult isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
			TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
			TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);

			// Specific
			TestResult isLessThanOrEqualTo3(Layer_ptr &layer);
			TestResult isEqualTo3(Layer_ptr &layer);
			TestResult isEqualTo4(Layer_ptr &layer);
			TestResult isEqualTo5(Layer_ptr &layer);
			TestResult isEqualTo6(Layer_ptr &layer);
			TestResult isGreaterThanOrEqualTo6(Layer_ptr &layer);
		};

		namespace Helper
		{
			int		getCount(Layer_ptr &layer);
			double	getDistanceBetween(Point_ptr &p1, Point_ptr &p2);
		};
	};

	namespace Edge
	{
		namespace Angle
		{
			// Non-specific
			TestResult isLessThanX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isLessThanXSigned(Layer_ptr &layer, double x);
			TestResult isLessThanXUnsigned(Layer_ptr &layer, double x);
			TestResult isLessThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isLessThanOrEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isLessThanOrEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isGreaterThanXSigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanXUnsigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isGreaterThanOrEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanOrEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign);
			TestResult isBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign);
			TestResult isNotBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isNotBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isNotBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isNotBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y);

			// Specific
			// ...
		};
		
		namespace Helper
		{
			double getAngle(Edge_ptr &edge);
		};
	};

	namespace Edges
	{
		namespace Count
		{

		};

		namespace Helper
		{

		};
	};

	namespace Facet
	{
		namespace Area
		{

		};

		namespace Helper
		{

		};
	};

	namespace Facets
	{
		namespace Count
		{

		};

		namespace Helper
		{

		};
	};

	namespace Interface
	{
		namespace Angle
		{
			// Non-specific
			TestResult isLessThanX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isLessThanXSigned(Layer_ptr &layer, double x);
			TestResult isLessThanXUnsigned(Layer_ptr &layer, double x);
			TestResult isLessThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isLessThanOrEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isLessThanOrEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isGreaterThanXSigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanXUnsigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, double x, bool hasSign);
			TestResult isGreaterThanOrEqualToXSigned(Layer_ptr &layer, double x);
			TestResult isGreaterThanOrEqualToXUnsigned(Layer_ptr &layer, double x);
			TestResult isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign);
			TestResult isBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl, bool hasSign);
			TestResult isNotBetweenXAndYSigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isNotBetweenXAndYUnsigned(Layer_ptr &layer, double x, double y, bool incl);
			TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isNotBetweenXAndYInclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYInclusiveUnsigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y, bool hasSign);
			TestResult isNotBetweenXAndYExclusiveSigned(Layer_ptr &layer, double x, double y);
			TestResult isNotBetweenXAndYExclusiveUnsigned(Layer_ptr &layer, double x, double y);

			// Specific
			TestResult isLessThan90Unsigned(Layer_ptr &layer);
			TestResult isLessThan0Signed(Layer_ptr &layer);
			TestResult isEqualTo0Unsigned(Layer_ptr &layer);
			TestResult isEqualTo90Unsigned(Layer_ptr &layer);
			TestResult isEqualTo180Unsigned(Layer_ptr &layer);
			TestResult isGreaterThan0Signed(Layer_ptr &layer);
			TestResult isBetween0And60InclusiveUnsigned(Layer_ptr &layer);
		};

		namespace Position
		{
			// Non-specific
			// ..

			// Specfic
			// ..
		};

		namespace Helper
		{
			double getAngle(Layer_ptr &layer);
		};
	};

	namespace Boundary
	{
		namespace Count
		{
			namespace Generic
			{
				// Non-specific
				TestResult isLessThanX(Edges_ptr &bound, int x);
				TestResult isLessThanOrEqualToX(Edges_ptr &bound, int x);
				TestResult isEqualToX(Edges_ptr &bound, int x);
				TestResult isGreaterThanOrEqualToX(Edges_ptr &bound, int x);
				TestResult isGreaterThanX(Edges_ptr &bound, int x);
				TestResult isBetweenXAndY(Edges_ptr &bound, int x, int y, bool incl);
				TestResult isBetweenXAndYInclusive(Edges_ptr &bound, int x, int y);
				TestResult isBetweenXAndYExclusive(Edges_ptr &bound, int x, int y);
				TestResult isNotBetweenXAndY(Edges_ptr &bound, int x, int y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Edges_ptr &bound, int x, int y);
				TestResult isNotBetweenXAndYExclusive(Edges_ptr &bound, int x, int y);

				// Specific
				TestResult isEqualTo1(Edges_ptr &bound);
				TestResult isEqualTo2(Edges_ptr &bound);
				TestResult isEqualTo3(Edges_ptr &bound);
			};
			namespace Left
			{
				// Non-specific
				TestResult isLessThanX(Layer_ptr &layer, int x);
				TestResult isLessThanOrEqualToX(Layer_ptr &layer, int x);
				TestResult isEqualToX(Layer_ptr &layer, int x);
				TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, int x);
				TestResult isGreaterThanX(Layer_ptr &layer, int x);
				TestResult isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
				TestResult isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
				TestResult isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);
				TestResult isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
				TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);

				// Specific
				TestResult isEqualTo1(Layer_ptr &layer);
				TestResult isEqualTo2(Layer_ptr &layer);
				TestResult isEqualTo3(Layer_ptr &layer);
			};

			namespace Right
			{
				// Non-specific
				TestResult isLessThanX(Layer_ptr &layer, int x);
				TestResult isLessThanOrEqualToX(Layer_ptr &layer, int x);
				TestResult isEqualToX(Layer_ptr &layer, int x);
				TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, int x);
				TestResult isGreaterThanX(Layer_ptr &layer, int x);
				TestResult isBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
				TestResult isBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
				TestResult isBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);
				TestResult isNotBetweenXAndY(Layer_ptr &layer, int x, int y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, int x, int y);
				TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, int x, int y);

				// Specific
				TestResult isEqualTo1(Layer_ptr &layer);
				TestResult isEqualTo2(Layer_ptr &layer);
				TestResult isEqualTo3(Layer_ptr &layer);
			};
		};

		namespace Length
		{
			namespace Generic
			{
				// Non-specific
				TestResult isLessThanX(Edges_ptr &bound, double x);
				TestResult isLessThanOrEqualToX(Edges_ptr &bound, double x);
				TestResult isEqualToX(Edges_ptr &bound, double x);
				TestResult isGreaterThanOrEqualToX(Edges_ptr &bound, double x);
				TestResult isGreaterThanX(Edges_ptr &bound, double x);
				TestResult isBetweenXAndY(Edges_ptr &bound, double x, double y, bool incl);
				TestResult isBetweenXAndYInclusive(Edges_ptr &bound, double x, double y);
				TestResult isBetweenXAndYExclusive(Edges_ptr &bound, double x, double y);
				TestResult isNotBetweenXAndY(Edges_ptr &bound, double x, double y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Edges_ptr &bound, double x, double y);
				TestResult isNotBetweenXAndYExclusive(Edges_ptr &bound, double x, double y);

				// Specific
				// ...
			};

			namespace Left
			{
				// Non-specific
				TestResult isLessThanX(Layer_ptr &layer, double x);
				TestResult isLessThanOrEqualToX(Layer_ptr &layer, double x);
				TestResult isEqualToX(Layer_ptr &layer, double x);
				TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, double x);
				TestResult isGreaterThanX(Layer_ptr &layer, double x);
				TestResult isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl);
				TestResult isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y);
				TestResult isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y);
				TestResult isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y);
				TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y);

				// Specific
				// ...
			};

			namespace Right
			{
				// Non-specific
				TestResult isLessThanX(Layer_ptr &layer, double x);
				TestResult isLessThanOrEqualToX(Layer_ptr &layer, double x);
				TestResult isEqualToX(Layer_ptr &layer, double x);
				TestResult isGreaterThanOrEqualToX(Layer_ptr &layer, double x);
				TestResult isGreaterThanX(Layer_ptr &layer, double x);
				TestResult isBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl);
				TestResult isBetweenXAndYInclusive(Layer_ptr &layer, double x, double y);
				TestResult isBetweenXAndYExclusive(Layer_ptr &layer, double x, double y);
				TestResult isNotBetweenXAndY(Layer_ptr &layer, double x, double y, bool incl);
				TestResult isNotBetweenXAndYInclusive(Layer_ptr &layer, double x, double y);
				TestResult isNotBetweenXAndYExclusive(Layer_ptr &layer, double x, double y);

				// Specific
				// ...
			};
		};

		namespace Helper
		{
			void	getLengths(double* arr, Layer_ptr &layer);
			double	getLeftLength(Layer_ptr &layer);
			double	getRightLength(Layer_ptr &layer);
			void	getCounts(int* arr, Layer_ptr &layer);
			int		getLeftCount(Layer_ptr &layer);
			int		getRightCount(Layer_ptr &layer);
		};
	};

	namespace Surface
	{
		namespace Area
		{

		};

		namespace Helper
		{

		};
	};

	namespace Feature
	{
		namespace Helper
		{

		};
	};

	namespace Generic
	{
		TestResult isLessThanX(int val, int x);
		TestResult isLessThanOrEqualToX(int val, int x);
		TestResult isEqualToX(int val, int x);
		TestResult isGreaterThanOrEqualToX(int val, int x);
		TestResult isGreaterThanX(int val, int x);
		TestResult isBetweenXAndY(int val, int x, int y, bool incl);
		TestResult isBetweenXAndYInclusive(int val, int x, int y);
		TestResult isBetweenXAndYExclusive(int val, int x, int y);
		TestResult isNotBetweenXAndY(int val, int x, int y, bool incl);
		TestResult isNotBetweenXAndYInclusive(int val, int x, int y);
		TestResult isNotBetweenXAndYExclusive(int val, int x, int y);
		TestResult isLessThanX(double val, double x, bool hasSign);
		TestResult isLessThanXSigned(double val, double x);
		TestResult isLessThanXUnsigned(double val, double x);
		TestResult isLessThanOrEqualToX(double val, double x, bool hasSign);
		TestResult isLessThanOrEqualToXSigned(double val, double x);
		TestResult isLessThanOrEqualToXUnsigned(double val, double x);
		TestResult isEqualToX(double val, double x, bool hasSign);
		TestResult isEqualToXSigned(double val, double x);
		TestResult isEqualToXUnsigned(double val, double x);
		TestResult isGreaterThanX(double val, double x, bool hasSign);
		TestResult isGreaterThanXSigned(double val, double x);
		TestResult isGreaterThanXUnsigned(double val, double x);
		TestResult isGreaterThanOrEqualToX(double val, double x, bool hasSign);
		TestResult isGreaterThanOrEqualToXSigned(double val, double x);
		TestResult isGreaterThanOrEqualToXUnsigned(double val, double x);
		TestResult isBetweenXAndY(double val, double x, double y, bool incl, bool hasSign);
		TestResult isBetweenXAndYSigned(double val, double x, double y, bool incl);
		TestResult isBetweenXAndYUnsigned(double val, double x, double y, bool incl);
		TestResult isBetweenXAndYInclusive(double val, double x, double y, bool hasSign);
		TestResult isBetweenXAndYInclusiveSigned(double val, double x, double y);
		TestResult isBetweenXAndYInclusiveUnsigned(double val, double x, double y);
		TestResult isBetweenXAndYExclusive(double val, double x, double y, bool hasSign);
		TestResult isBetweenXAndYExclusiveSigned(double val, double x, double y);
		TestResult isBetweenXAndYExclusiveUnsigned(double val, double x, double y);
		TestResult isNotBetweenXAndY(double val, double x, double y, bool incl, bool hasSign);
		TestResult isNotBetweenXAndYSigned(double val, double x, double y, bool incl);
		TestResult isNotBetweenXAndYUnsigned(double val, double x, double y, bool incl);
		TestResult isNotBetweenXAndYInclusive(double val, double x, double y, bool hasSign);
		TestResult isNotBetweenXAndYInclusiveSigned(double val, double x, double y);
		TestResult isNotBetweenXAndYInclusiveUnsigned(double val, double x, double y);
		TestResult isNotBetweenXAndYExclusive(double val, double x, double y, bool hasSign);
		TestResult isNotBetweenXAndYExclusiveSigned(double val, double x, double y);
		TestResult isNotBetweenXAndYExclusiveUnsigned(double val, double x, double y);
	};

	namespace Helper
	{
		void getRange(double* range, double val, double tol);
		void getRange(double* range, double val1, double val2, double tol);
	};
};

#endif