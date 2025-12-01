#include "pch.h"
#include "CppUnitTest.h"
#include <string.h>
#include <math.h>

#include <assert.h>
extern "C" {
	char* analyzeTriangle(int side1, int side2, int side3);
	float triArea(int side1, int side2, int side3);
	void triangleAngles(int side1, int side2, int side3, float angles[]);

	void sort4PointsXY(int points_x[], int points_y[], int sorted_x[], int sorted_y[]);
	void sort4PointsCCW(int points_x[], int points_y[], int sorted_points[]);
	char* isRectangle(int points_x[], int points_y[], int sorted_points[]);
	double shapePerimeter(int PointA[], int PointB[], int PointC[], int PointD[]);
	double RectArea(int PointA[], int PointB[], int PointC[]);
	double dOfPoints(int pointP[], int pointQ[]);
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestRectangle {
	//ALL TEST METHODS PASSED FOR SORT4POINTSXY -DW
	//tests all combinations of sorting arrangements (total 24/2 for unique combinations for points_x and points_y) -DW

	TEST_CLASS(DistanceTests)
	{
	public:

		TEST_METHOD(Distance_SamePoint_ReturnsZero)
		{
			int p[2] = { 0, 0 };   // same point P -FL
			int q[2] = { 0, 0 };   // same point Q -FL

			double result = dOfPoints(p, q); // distance should be 0 -FL

			Assert::AreEqual(0.0, result, 0.0001); // verify zero distance adding 0.0001 to avoid false positives -FL
		}

		TEST_METHOD(Distance_Horizontal_Positive)
		{
			int p[2] = { 0, 0 };   // start point -FL
			int q[2] = { 5, 0 };   // horizontal movement only -FL

			double result = dOfPoints(p, q); // expected distance = 5 -FL

			Assert::AreEqual(5.0, result, 0.0001); // check correct horizontal dist -FL
		}

		TEST_METHOD(Distance_Vertical_Positive)
		{
			int p[2] = { 2, 3 };   // start point -FL
			int q[2] = { 2, 10 };  // vertical movement only -FL

			double result = dOfPoints(p, q); // expected distance = 7 -FL

			Assert::AreEqual(7.0, result, 0.0001); // check correct vertical dist -FL
		}

		TEST_METHOD(Distance_Diagonal_Classic345)
		{
			int p[2] = { 0, 0 };   // start point -FL
			int q[2] = { 3, 4 };   // classic 3-4-5 triangle -FL

			double result = dOfPoints(p, q); // exected distance = 5 -FL

			Assert::AreEqual(5.0, result, 0.0001); // verify Pythagorean case -FL
		}

		TEST_METHOD(Distance_LargerNumbers)
		{
			int p[2] = { 10, 20 };   // shifted point -FL
			int q[2] = { 13, 24 };   // another point creating 3-4-5 distance -FL

			double result = dOfPoints(p, q); // expected distance = 5 -FL

			Assert::AreEqual(5.0, result, 0.0001); // ensure accuracy with larger coords -FL
		}
	};

	TEST_CLASS(Sorted4PointsXY) {

public:
	TEST_METHOD(sort4PointsXY_001)
	{
		int points_x[4] = { 10, 20, 30, 40 };
		int points_y[4] = { 40, 30, 20, 10 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 1, 2, 3 };
		int expected_sorted_y[4] = { 3, 2, 1, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_002)
	{
		int points_x[4] = { 10, 20, 40, 30 };
		int points_y[4] = { 40, 30, 10, 20 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 1, 3, 2 };
		int expected_sorted_y[4] = { 2, 3, 1, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_003)
	{
		int points_x[4] = { 10, 30, 20, 40 };
		int points_y[4] = { 40, 20, 30, 10 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 2, 1, 3 };
		int expected_sorted_y[4] = { 3, 1, 2, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_004)
	{
		int points_x[4] = { 10, 30, 40, 20 };
		int points_y[4] = { 40, 20, 10, 30 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 3, 1, 2 };
		int expected_sorted_y[4] = { 2, 1, 3, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_005)
	{
		int points_x[4] = { 10, 40, 20, 30 };
		int points_y[4] = { 40, 10, 30, 20 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 2, 3, 1 };
		int expected_sorted_y[4] = { 1, 3, 2, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_006)
	{
		int points_x[4] = { 10, 40, 30, 20 };
		int points_y[4] = { 40, 10, 20, 30 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 0, 3, 2, 1 };
		int expected_sorted_y[4] = { 1, 2, 3, 0 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_007)
	{
		int points_x[4] = { 20, 10, 30, 40 };
		int points_y[4] = { 30, 40, 20, 10 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 1, 0, 2, 3 };
		int expected_sorted_y[4] = { 3, 2, 0, 1 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_008)
	{
		int points_x[4] = { 20, 10, 40, 30 };
		int points_y[4] = { 30, 40, 10, 20 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 1, 0, 3, 2 };
		int expected_sorted_y[4] = { 2, 3, 0, 1 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_009)
	{
		int points_x[4] = { 20, 30, 10, 40 };
		int points_y[4] = { 30, 20, 40, 10 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 2, 0, 1, 3 };
		int expected_sorted_y[4] = { 3, 1, 0, 2 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_010)
	{
		int points_x[4] = { 20, 30, 40, 10 };
		int points_y[4] = { 30, 20, 10, 40 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 3, 0, 1, 2 };
		int expected_sorted_y[4] = { 2, 1, 0, 3 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_011)
	{
		int points_x[4] = { 20, 40, 10, 30 };
		int points_y[4] = { 30, 10, 40, 20 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 2, 0, 3, 1 };
		int expected_sorted_y[4] = { 1, 3, 0, 2 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}

	TEST_METHOD(sort4PointsXY_012)
	{
		int points_x[4] = { 20, 40, 30, 10 };
		int points_y[4] = { 30, 10, 20, 40 };
		int sorted_x[4] = { -1, -1, -1, -1 };
		int sorted_y[4] = { -1, -1, -1, -1 };
		int expected_sorted_x[4] = { 3, 0, 2, 1 };
		int expected_sorted_y[4] = { 1, 2, 0, 3 };
		sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected_sorted_x[x], sorted_x[x]);
			Assert::AreEqual(expected_sorted_y[x], sorted_y[x]);
		}
	}
	};

	TEST_CLASS(Sorted4PointsCCW) {

public:

	TEST_METHOD(sort4PointsCCW_AxisAlignedRectangle_001)
	{
		int points_X[4] = { 6, 22, 22, 6 };
		int points_Y[4] = { 16, 20, 16, 20 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 2, 1, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_AxisAlignedRectangle_002)
	{
		int points_X[4] = { 46, 40, 40, 46 };
		int points_Y[4] = { 6, 16, 6, 16 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 0, 3, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_AxisAlignedRectangle_003)
	{
		int points_X[4] = { 12, 6, 12, 6 };
		int points_Y[4] = { 2, 2, 8, 8 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_001)
	{
		int points_X[4] = { 15, 3, 16, 2 };
		int points_Y[4] = { 19, 5, 6, 18 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 0, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_002)
	{
		int points_X[4] = { 19, 10, 11, 18 };
		int points_Y[4] = { 3, 10, 2, 11 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 0, 3, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_003)
	{
		int points_X[4] = { 7, 10, 2, 15 };
		int points_Y[4] = { 9, 22, 14, 17 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 3, 1, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_004)
	{
		int points_X[4] = { 23, 15, 18, 20 };
		int points_Y[4] = { 3, 5, 0, 8 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 0, 3, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_005)
	{
		int points_X[4] = { 7, 20, 14, 13 };
		int points_Y[4] = { 14, 3, 17, 0 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 1, 2, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

		TEST_METHOD(sort4PointsCCW_SlantedRectangle_006)
	{
		int points_X[4] = { 9, 13, 15, 19 };
		int points_Y[4] = { 3, 0, 11, 8 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 3, 2, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_007)
	{
		int points_X[4] = { 38, 20, 35, 23 };
		int points_Y[4] = { 5, 9, 14, 0 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 0, 2, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_SlantedRectangle_008)
	{
		int points_X[4] = { 15, 10, 5, 10 };
		int points_Y[4] = { 5, 0, 5, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 3, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_4DifferentPoints_Lines_001)
	{
		int points_X[4] = { 20, 15, 25, 10 };
		int points_Y[4] = { 15, 10, 20, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 1, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_4DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 20, 20 };
		int points_Y[4] = { 15, 10, 25, 20 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 3, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_4DifferentPoints_Lines_003)
	{
		int points_X[4] = { 25, 15, 10, 20 };
		int points_Y[4] = { 10, 20, 25, 15 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 3, 1, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_4DifferentPoints_Lines_004)
	{
		int points_X[4] = { 15, 20, 5, 10 };
		int points_Y[4] = { 20, 20, 20, 20 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_2DifferentPoints_Lines_001)
	{
		int points_X[4] = { 25, 10, 25, 10};
		int points_Y[4] = { 20, 5, 20, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 3, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_2DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 20, 20 };
		int points_Y[4] = { 25, 10, 10, 25 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 0, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_2DifferentPoints_Lines_003)
	{
		int points_X[4] = { 10, 25, 25, 10 };
		int points_Y[4] = { 25, 10, 10, 25 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 0, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_2DifferentPoints_Lines_004)
	{
		int points_X[4] = { 20, 20, 5, 5 };
		int points_Y[4] = { 20, 20, 20, 20 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_TriangleDegenerate_001)
	{
		int points_X[4] = { 20, 15, 10, 30 };
		int points_Y[4] = { 15, 10, 5, 7 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_TriangleDegenerate_002)
	{
		int points_X[4] = { 20, 15, 10, 5 };
		int points_Y[4] = { 15, 10, 5, 50 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 1, 0, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_TriangleDegenerate_003)
	{
		int points_X[4] = { 15, 10, 25, 17 };
		int points_Y[4] = { 20, 25, 10, 30 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_TriangleDegenerate_004)
{
		int points_X[4] = { 15, 10, 25, 17 };
		int points_Y[4] = { 20, 25, 10, 12 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 0, 1, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_4SamePoints_001)
	{
		int points_X[4] = { 24, 24, 24, 24 };
		int points_Y[4] = { 14, 14, 14, 14 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 1, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_001)
	{
		int points_X[4] = { 0, 15, 20, 5 };
		int points_Y[4] = { 0, 0, 10, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 1, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_002)
	{
		int points_X[4] = { 6, 6, 14, 14 };
		int points_Y[4] = { 6, 16, 12, 22 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 2, 3, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_003)
	{
		int points_X[4] = { 8, 12, 16, 12 };
		int points_Y[4] = { 14, 22, 14, 6 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_004)
	{
		int points_X[4] = { 10, 10, 16, 16 };
		int points_Y[4] = { 22, 14, 16, 8 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_005)
	{
		int points_X[4] = { 20, 28, 26, 34 };
		int points_Y[4] = { 10, 10, 4, 4 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Parallelogram_006)
	{
		int points_X[4] = { 14, 22, 30, 22 };
		int points_Y[4] = { 14, 10, 14, 18 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 3, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_001)
	{
		int points_X[4] = { 19, 16, 16, 15 };
		int points_Y[4] = { 10, 9, 11, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_002)
	{
		int points_X[4] = { 13, 25, 16, 16 };
		int points_Y[4] = { 10, 10, 13, 7 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 1, 2, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_003)
	{
		int points_X[4] = { 20, 15, 25, 20 };
		int points_Y[4] = { 15, 10, 10, 0 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_004)
	{
		int points_X[4] = { 25, 20, 10, 10 };
		int points_Y[4] = { 0, 15, 5, 15 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 1, 3, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_005)
	{
		int points_X[4] = { 15, 10, 5, 10 };
		int points_Y[4] = { 5, 0, 5, 15 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 3, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_006)
	{
		int points_X[4] = { 35, 20, 25, 35 };
		int points_Y[4] = { 20, 5, 20, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 3, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_007)
	{
		int points_X[4] = { 30, 0, 30, 40 };
		int points_Y[4] = { 20, 10, 0, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_008)
	{
		int points_X[4] = { 30, 10, 30, 20 };
		int points_Y[4] = { 10, 20, 0, 0 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Kite_009)
	{
		int points_X[4] = { 15, 10, 7, 19 };
		int points_Y[4] = { 5, 15, 7, 14 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 3, 1, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}
	TEST_METHOD(sort4PointsCCW_Trapezium_001)
	{
		int points_X[4] = { 35, 15, 25, 35 };
		int points_Y[4] = { 20, 5, 20, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 3, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_002)
	{
		int points_X[4] = { 15, 15, 0, 5 };
		int points_Y[4] = { 0, 5, 0, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 0, 1, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_003)
	{
		int points_X[4] = { 5, 5, 10, 10 };
		int points_Y[4] = { 15, 0, 0, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 3, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_004)
	{
		int points_X[4] = { 20, 5, 5, 15 };
		int points_Y[4] = { 10, 10, 5, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_005)
	{
		int points_X[4] = { 5, 20, 20, 10 };
		int points_Y[4] = { 5, 20, 10, 0 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_006)
	{
		int points_X[4] = { 15, 10, 15, 10 };
		int points_Y[4] = { 5, 20, 20, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 2, 1, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}



	//real one
	TEST_METHOD(sort4PointsCCW_Trapezium_007)
	{
		int points_X[4] = { 25, 10, 20, 10 };
		int points_Y[4] = { 20, 5, 25, 15 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_008)
	{
		int points_X[4] = { 15, 10, 20, 30 };
		int points_Y[4] = { 20, 15, 5, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Trapezium_009)
	{
		int points_X[4] = { 15, 0, 20, 10 };
		int points_Y[4] = { 5, 20, 10, 20 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 2, 3, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_001)
	{
		int points_X[4] = { 25, 10, 15, 10 };
		int points_Y[4] = { 20, 5, 20, 15 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 0, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_002)
	{
		int points_X[4] = { 3, 6, 1, 7 };
		int points_Y[4] = { 4, 3, 3, 1 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 1, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_003)
	{
		int points_X[4] = { 3, 3, 5, 5 };
		int points_Y[4] = { 5, 2, 1, 6 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_004)
	{
		int points_X[4] = { 14, 16, 14, 16 };
		int points_Y[4] = { 5, 6, 10, 9 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 1, 3, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_005)
	{
		int points_X[4] = { 5, 7, 9, 9 };
		int points_Y[4] = { 9, 9, 5, 7 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_006)
	{
		int points_X[4] = { 11, 15, 15, 13 };
		int points_Y[4] = { 5, 7, 9, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 3, 1, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_007)
	{
		int points_X[4] = { 4, 6, 4, 8 };
		int points_Y[4] = { 11, 7, 9, 7 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 3, 0, 2 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_008)
	{
		int points_X[4] = { 9, 4, 5, 8 };
		int points_Y[4] = { 7, 7, 5, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IsocelesTrapezium_009)
	{
		int points_X[4] = { 10, 8, 8, 12 };
		int points_Y[4] = { 10, 8, 6, 10 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 0, 1 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}
	TEST_METHOD(sort4PointsCCW_IrregularParallelogram_001)
	{
		int points_X[4] = { 10, 20, 15, 11 };
		int points_Y[4] = { 10, 15, 5, 14 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 1, 3, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_IrregularParallelogram_002)
	{
		int points_X[4] = { 3, 6, 2, 7 };
		int points_Y[4] = { 4, 3, 2, 2 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Concave_001)
	{
		int points_X[4] = { 4, 5, 7, 8 };
		int points_Y[4] = { 10, 9, 9, 4 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 3, 2, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Concave_002)
	{
		int points_X[4] = { 9, 12, 11, 8 };
		int points_Y[4] = { 7, 12, 11, 12 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 0, 1, 2, 3 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Concave_003)
	{
		int points_X[4] = { 13, 13, 10, 14 };
		int points_Y[4] = { 10, 9, 5, 5 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 2, 3, 1, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	TEST_METHOD(sort4PointsCCW_Concave_004)
	{
		int points_X[4] = { 15, 17, 19, 17 };
		int points_Y[4] = { 9, 5, 9, 6 };
		int sorted_points[4] = { -1, -1, -1, -1 };
		int expected[4] = { 1, 2, 3, 0 };
		sort4PointsCCW(points_X, points_Y, sorted_points);

		for (int x = 0; x < 4; x++) {

			Assert::AreEqual(expected[x], sorted_points[x]);
		}
	}

	};

	TEST_CLASS(IsRectangle) {

public:

	TEST_METHOD(isRectangle_AxisAlignedRectangle_001)
	{
		int points_X[4] = { 6, 22, 22, 6 };
		int points_Y[4] = { 16, 20, 16, 20 };
		int sorted_points[4] = { 0, 2, 1, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_AxisAlignedRectangle_002)
	{
		int points_X[4] = { 46, 40, 40, 46 };
		int points_Y[4] = { 6, 16, 6, 16 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_AxisAlignedRectangle_003)
	{
		int points_X[4] = { 12, 6, 12, 6 };
		int points_Y[4] = { 2, 2, 8, 8 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_001)
	{
		int points_X[4] = { 15, 3, 16, 2 };
		int points_Y[4] = { 19, 5, 6, 18 };
		int sorted_points[4] = { 1, 2, 0, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_002)
	{
		int points_X[4] = { 19, 10, 11, 18 };
		int points_Y[4] = { 3, 10, 2, 11 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_003)
	{
		int points_X[4] = { 7, 10, 2, 15 };
		int points_Y[4] = { 9, 22, 14, 17 };
		int sorted_points[4] = { 0, 3, 1, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_004)
	{
		int points_X[4] = { 23, 15, 18, 20 };
		int points_Y[4] = { 3, 5, 0, 8 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_005)
	{
		int points_X[4] = { 7, 20, 14, 13 };
		int points_Y[4] = { 14, 3, 17, 0 };
		int sorted_points[4] = { 3, 1, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_006)
	{
		int points_X[4] = { 9, 13, 15, 19 };
		int points_Y[4] = { 3, 0, 11, 8 };
		int sorted_points[4] = { 1, 3, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_007)
	{
		int points_X[4] = { 38, 20, 35, 23 };
		int points_Y[4] = { 5, 9, 14, 0 };
		int sorted_points[4] = { 3, 0, 2, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_008)
	{
		int points_X[4] = { 15, 10, 5, 10 };
		int points_Y[4] = { 5, 0, 5, 10 };
		int sorted_points[4] = { 1, 0, 3, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4DifferentPoints_Lines_001)
	{
		int points_X[4] = { 20, 15, 25, 10 };
		int points_Y[4] = { 15, 10, 20, 5 };
		int sorted_points[4] = { 3, 1, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 20, 20 };
		int points_Y[4] = { 15, 10, 25, 20 };
		int sorted_points[4] = { 1, 0, 3, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_2DifferentPoints_Lines_001)
	{
		int points_X[4] = { 25, 10, 25, 10 };
		int points_Y[4] = { 20, 5, 20, 5 };
		int sorted_points[4] = { 1, 3, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_2DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 5, 5 };
		int points_Y[4] = { 20, 20, 20, 20 };
		int sorted_points[4] = { 2, 3, 0, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_TriangleDegenerate_001)
	{
		int points_X[4] = { 20, 15, 10, 30 };
		int points_Y[4] = { 15, 10, 5, 7 };
		int sorted_points[4] = { 2, 3, 0, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_TriangleDegenerate_002)
	{
		int points_X[4] = { 20, 15, 10, 5 };
		int points_Y[4] = { 15, 10, 5, 50 };
		int sorted_points[4] = { 2, 1, 0, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4SamePoints)
	{
		int points_X[4] = { 24, 24, 24, 24 };
		int points_Y[4] = { 14, 14, 14, 14 };
		int sorted_points[4] = { 0, 1, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Parallelogram_001)
	{
		int points_X[4] = { 0, 15, 20, 5 };
		int points_Y[4] = { 0, 0, 10, 10 };
		int sorted_points[4] = { 0, 1, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Parallelogram_002)
	{
		int points_X[4] = { 6, 6, 14, 14 };
		int points_Y[4] = { 6, 16, 12, 22 };
		int sorted_points[4] = { 0, 2, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Kite_001)
	{
		int points_X[4] = { 19, 16, 16, 15 };
		int points_Y[4] = { 10, 9, 11, 10 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Kite_002)
	{
		int points_X[4] = { 13, 25, 16, 16 };
		int points_Y[4] = { 10, 10, 13, 7 };
		int sorted_points[4] = { 3, 1, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}
	TEST_METHOD(isRectangle_Trapezium_001)
	{
		int points_X[4] = { 35, 15, 25, 35 };
		int points_Y[4] = { 20, 5, 20, 10 };
		int sorted_points[4] = { 1, 3, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Trapezium_002)
	{
		int points_X[4] = { 15, 15, 0, 5 };
		int points_Y[4] = { 0, 5, 0, 5 };
		int sorted_points[4] = { 2, 0, 1, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IsocelesTrapezium_001)
	{
		int points_X[4] = { 25, 10, 15, 10 };
		int points_Y[4] = { 20, 5, 20, 15 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IsocelesTrapezium_002)
	{
		int points_X[4] = { 3, 6, 1, 7 };
		int points_Y[4] = { 4, 3, 3, 1 };
		int sorted_points[4] = { 3, 1, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}
	TEST_METHOD(isRectangle_IrregularParallelogram_001)
	{
		int points_X[4] = { 10, 20, 15, 11 };
		int points_Y[4] = { 10, 15, 5, 14 };
		int sorted_points[4] = { 2, 1, 3, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IrregularParallelogram_002)
	{
		int points_X[4] = { 3, 6, 2, 7 };
		int points_Y[4] = { 4, 3, 2, 2 };
		int sorted_points[4] = { 2, 3, 1, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Concave_001)
	{
		int points_X[4] = { 4, 5, 7, 8 };
		int points_Y[4] = { 10, 9, 9, 4 };
		int sorted_points[4] = { 3, 2, 1, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Concave_002)
	{
		int points_X[4] = { 9, 12, 11, 8 };
		int points_Y[4] = { 7, 12, 11, 12 };
		int sorted_points[4] = { 0, 2, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a rectangle") == 0);
	}
	};
	TEST_CLASS(RectanglePerimeter) {

public:

	TEST_METHOD(shapePerimeter_AxisAlignedRectangle_001)
	{
		int pointA[2] = { 6, 16 };
		int pointB[2] = { 22, 16 };
		int pointC[2] = { 22, 20 };
		int pointD[2] = { 6, 20 };
		double expected = 40.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_AxisAlignedRectangle_002)
	{
		int pointA[2] = { 40, 6 };
		int pointB[2] = { 46, 6 };
		int pointC[2] = { 46, 16 };
		int pointD[2] = { 40, 16 };
		double expected = 32.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_AxisAlignedRectangle_003)
	{
		int pointA[2] = { 6, 2 };
		int pointB[2] = { 12, 2 };
		int pointC[2] = { 12, 8 };
		int pointD[2] = { 6, 8 };
		double expected = 24.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_001)
	{
		int pointA[2] = { 3, 5 };
		int pointB[2] = { 16, 6 };
		int pointC[2] = { 15, 19 };
		int pointD[2] = { 2, 18 };
		double expected = 52.152;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_002)
	{
		int pointA[2] = { 11, 2 };
		int pointB[2] = { 19, 3 };
		int pointC[2] = { 18, 11 };
		int pointD[2] = { 10, 10 };
		double expected = 32.248;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_003)
	{
		int pointA[2] = { 7, 9 };
		int pointB[2] = { 15, 17 };
		int pointC[2] = { 10, 22 };
		int pointD[2] = { 2, 14 };
		double expected = 36.769;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_004)
	{
		int pointA[2] = { 18, 0 };
		int pointB[2] = { 23, 3 };
		int pointC[2] = { 20, 8 };
		int pointD[2] = { 15, 5 };
		double expected = 23.323;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_005)
	{
		int pointA[2] = { 13, 0 };
		int pointB[2] = { 20, 3 };
		int pointC[2] = { 14, 17 };
		int pointD[2] = { 7, 14 };
		double expected = 45.694;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_006)
	{
		int pointA[2] = { 13, 0 };
		int pointB[2] = { 19, 8 };
		int pointC[2] = { 15, 11 };
		int pointD[2] = { 9, 3 };
		double expected = 30.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_007)
	{
		int pointA[2] = { 23, 0 };
		int pointB[2] = { 38, 5 };
		int pointC[2] = { 35, 14 };
		int pointD[2] = { 20, 9 };
		double expected = 50.596;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_SlantedRectangle_008)
	{
		int pointA[2] = { 10, 0 };
		int pointB[2] = { 15, 5 };
		int pointC[2] = { 10, 10 };
		int pointD[2] = { 5, 5 };
		double expected = 28.28;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_4DifferentPoints_Lines_001)
	{
		int pointA[2] = { 10, 5 };
		int pointB[2] = { 15, 10 };
		int pointC[2] = { 20, 15 };
		int pointD[2] = { 25, 20 };
		double expected = 42.426;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_4DifferentPoints_Lines_002)
	{
		int pointA[2] = { 20, 10 };
		int pointB[2] = { 20, 15 };
		int pointC[2] = { 20, 20 };
		int pointD[2] = { 20, 25 };
		double expected = 30.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_2DifferentPoints_Lines_001)
	{
		int pointA[2] = { 10, 5 };
		int pointB[2] = { 10, 5 };
		int pointC[2] = { 25, 20 };
		int pointD[2] = { 25, 20 };
		double expected = 42.426;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_2DifferentPoints_Lines_002)
	{
		int pointA[2] = { 5, 20 };
		int pointB[2] = { 5, 20 };
		int pointC[2] = { 20, 20 };
		int pointD[2] = { 20, 20 };
		double expected = 30.00;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_TriangleDegenerate_001)
	{
		int pointA[2] = { 10, 5 };
		int pointB[2] = { 30, 7 };
		int pointC[2] = { 20, 15 };
		int pointD[2] = { 15, 10 };
		double expected = 47.047;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_TriangleDegenerate_002)
	{
		int pointA[2] = { 10, 5 };
		int pointB[2] = { 15, 10 };
		int pointC[2] = { 20, 15 };
		int pointD[2] = { 5, 50 };
		double expected = 97.498;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_4SamePoints)
	{
		int pointA[2] = { 24, 14 };
		int pointB[2] = { 24, 14 };
		int pointC[2] = { 24, 14 };
		int pointD[2] = { 24, 14 };
		double expected = 0;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Parallelogram_001)
	{
		int pointA[2] = { 0, 0 };
		int pointB[2] = { 15, 0 };
		int pointC[2] = { 20, 10 };
		int pointD[2] = { 5, 10 };
		double expected = 52.360;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Parallelogram_002)
	{
		int pointA[2] = { 6, 6 };
		int pointB[2] = { 14, 12 };
		int pointC[2] = { 14, 22 };
		int pointD[2] = { 6, 16 };
		double expected = 40;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Kite_001)
	{
		int pointA[2] = { 16, 9 };
		int pointB[2] = { 19, 10 };
		int pointC[2] = { 16, 11 };
		int pointD[2] = { 15, 10 };
		double expected = 9.152;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Kite_002)
	{
		int pointA[2] = { 16, 7 };
		int pointB[2] = { 25, 10 };
		int pointC[2] = { 16, 13 };
		int pointD[2] = { 13, 10 };
		double expected = 27.460;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Trapisum_001)
	{
		int pointA[2] = { 15, 5 };
		int pointB[2] = { 35, 10 };
		int pointC[2] = { 35, 20 };
		int pointD[2] = { 25, 20 };
		double expected = 58.644;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Trapisum_002)
	{
		int pointA[2] = { 0, 0 };
		int pointB[2] = { 15, 0 };
		int pointC[2] = { 15, 5 };
		int pointD[2] = { 5, 5 };
		double expected = 37.071;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_IsocelesTrapisum_001)
	{
		int pointA[2] = { 10, 5 };
		int pointB[2] = { 25, 20 };
		int pointC[2] = { 15, 20 };
		int pointD[2] = { 10, 15 };
		double expected = 48.284;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_IsocelesTrapisum_002)
	{
		int pointA[2] = { 7, 1 };
		int pointB[2] = { 6, 3 };
		int pointC[2] = { 3, 4 };
		int pointD[2] = { 1, 3 };
		double expected = 13.959;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_IrregularParallelogram_001)
	{
		int pointA[2] = { 15, 5 };
		int pointB[2] = { 20, 15 };
		int pointC[2] = { 11, 14 };
		int pointD[2] = { 10, 10 };
		double expected = 31.429;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_IrregularParallelogram_002)
	{
		int pointA[2] = { 2, 2 };
		int pointB[2] = { 7, 2 };
		int pointC[2] = { 6, 3 };
		int pointD[2] = { 3, 4 };
		double expected = 11.812;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Concave_001)
	{
		int pointA[2] = { 8, 4 };
		int pointB[2] = { 7, 9 };
		int pointC[2] = { 5, 9 };
		int pointD[2] = { 4, 10 };
		double expected = 15.724;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}

	TEST_METHOD(shapePerimeter_Concave_002)
	{
		int pointA[2] = { 9, 7 };
		int pointB[2] = { 11, 11 };
		int pointC[2] = { 8, 12 };
		int pointD[2] = { 12, 12 };
		double expected = 17.465;
		double tolerance = 0.01;

		Assert::IsTrue((shapePerimeter(pointA, pointB, pointC, pointD) < expected + tolerance)
			&& (shapePerimeter(pointA, pointB, pointC, pointD) > expected - tolerance));
	}
	};
	TEST_CLASS(RectangleArea) {

public:

	TEST_METHOD(RectArea_AxisAlignedRectangle_001)
	{
		int pointA[2] = { 6, 16 };
		int pointB[2] = { 22, 16 };
		int pointC[2] = { 22, 20 };
		double expected = 64.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_AxisAlignedRectangle_002)
	{
		int pointA[2] = { 40, 6 };
		int pointB[2] = { 46, 6 };
		int pointC[2] = { 46, 16 };
		double expected = 60.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_AxisAlignedRectangle_003)
	{
		int pointA[2] = { 6, 2 };
		int pointB[2] = { 12, 2 };
		int pointC[2] = { 12, 8 };
		float expected = 36.00;
		float tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_001)
	{
		int pointA[2] = { 3, 5 };
		int pointB[2] = { 16, 6 };
		int pointC[2] = { 15, 19 };
		double expected = 170.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_002)
	{
		int pointA[2] = { 11, 2 };
		int pointB[2] = { 19, 3 };
		int pointC[2] = { 18, 11 };
		double expected = 65.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_003)
	{
		int pointA[2] = { 7, 9 };
		int pointB[2] = { 15, 17 };
		int pointC[2] = { 10, 22 };
		double expected = 80.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_004)
	{
		int pointA[2] = { 18, 0 };
		int pointB[2] = { 23, 3 };
		int pointC[2] = { 20, 8 };
		double expected = 34.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_005)
	{
		int pointA[2] = { 13, 0 };
		int pointB[2] = { 20, 3 };
		int pointC[2] = { 14, 17 };
		double expected = 116.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_006)
	{
		int pointA[2] = { 13, 0 };
		int pointB[2] = { 19, 8 };
		int pointC[2] = { 15, 11 };
		double expected = 50.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_007)
	{
		int pointA[2] = { 23, 0 };
		int pointB[2] = { 38, 5 };
		int pointC[2] = { 35, 14 };
		double expected = 150.00;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}

	TEST_METHOD(RectArea_SlantedRectangle_008)
	{
		int pointA[2] = { 10, 0 };
		int pointB[2] = { 15, 5 };
		int pointC[2] = { 10, 10 };
		double expected = 50;
		double tolerance = 0.01;

		Assert::IsTrue((RectArea(pointA, pointB, pointC) < expected + tolerance)
			&& (RectArea(pointA, pointB, pointC) > expected - tolerance));
	}
	};
};
	
	
		
	


	// Helper for float comparison
	static bool ApproxEqual(float a, float b, float eps = 0.01f)
	{
		return fabs(a - b) <= eps;
	}
	namespace TestTriangle
	{

		TEST_CLASS(TriangleTypeTests)
		{
		public:

			TEST_METHOD(NotTriangle_ZeroOrNegative)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(0, 3, 4), "Not a triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(-1, 3, 3), "Not a triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(3, -2, 3), "Not a triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(3, 3, -5), "Not a triangle") == 0);
			}

			TEST_METHOD(NotTriangle_InequalityFails)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(1, 2, 100), "Not a triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(2, 3, 5), "Not a triangle") == 0);
			}

			TEST_METHOD(Equilateral_333)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(3, 3, 3), "Equilateral triangle") == 0);
			}

			TEST_METHOD(Isosceles_AllPermutations_445)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(4, 4, 5), "Isosceles triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(4, 5, 4), "Isosceles triangle") == 0);
				Assert::IsTrue(strcmp(analyzeTriangle(5, 4, 4), "Isosceles triangle") == 0);
			}

			TEST_METHOD(Scalene_345)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(3, 4, 5), "Scalene triangle") == 0);
			}

			TEST_METHOD(Scalene_456)
			{
				Assert::IsTrue(strcmp(analyzeTriangle(4, 5, 6), "Scalene triangle") == 0);
			}
		};



		TEST_CLASS(TriAreaTests)
		{
		public:

			TEST_METHOD(InvalidSides_ReturnNegative)
			{
				Assert::IsTrue(triArea(0, 3, 4) < 0);
				Assert::IsTrue(triArea(-1, 3, 4) < 0);
				Assert::IsTrue(triArea(1, 2, 100) < 0);
			}

			TEST_METHOD(Area_ThreeFourFive_IsSix)
			{
				Assert::IsTrue(ApproxEqual(triArea(3, 4, 5), 6.0f));
			}

			TEST_METHOD(Area_EquilateralSide2)
			{
				Assert::IsTrue(ApproxEqual(triArea(2, 2, 2), 1.732f, 0.01f));
			}

			TEST_METHOD(Area_Scalene_456)
			{
				// Heron's formula = 9.92
				Assert::IsTrue(ApproxEqual(triArea(4, 5, 6), 9.92f, 0.05f));
			}
		};



		TEST_CLASS(TriAnglesTests)
		{
		public:

			TEST_METHOD(InvalidTriangle_AllAnglesNegative)
			{
				float angles[3];
				triangleAngles(1, 2, 100, angles);

				Assert::IsTrue(angles[0] < 0);
				Assert::IsTrue(angles[1] < 0);
				Assert::IsTrue(angles[2] < 0);
			}

			TEST_METHOD(Equilateral_AllAngles60)
			{
				float angles[3];
				triangleAngles(3, 3, 3, angles);

				Assert::IsTrue(ApproxEqual(angles[0], 60.0f, 0.3f));
				Assert::IsTrue(ApproxEqual(angles[1], 60.0f, 0.3f));
				Assert::IsTrue(ApproxEqual(angles[2], 60.0f, 0.3f));
			}

			TEST_METHOD(ThreeFourFive_Has90DegreeAngle_AndSum180)
			{
				float angles[3];
				triangleAngles(3, 4, 5, angles);

				// biggest side is 5 angle2 should be 90-ish
				Assert::IsTrue(ApproxEqual(angles[2], 90.0f, 0.5f));

				float sum = angles[0] + angles[1] + angles[2];
				Assert::IsTrue(ApproxEqual(sum, 180.0f, 0.5f));
			}

			TEST_METHOD(Isosceles_TwoAnglesMatch)
			{
				float angles[3];
				triangleAngles(5, 5, 8, angles);

				Assert::IsTrue(
					ApproxEqual(angles[0], angles[1], 0.5f) ||
					ApproxEqual(angles[0], angles[2], 0.5f) ||
					ApproxEqual(angles[1], angles[2], 0.5f)
				);
			}
		};

	}