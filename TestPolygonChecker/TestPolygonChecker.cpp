#include "pch.h"
#include "CppUnitTest.h"
#include <string.h>
#include <math.h>

#include <assert.h>
extern "C" {
	char* analyzeTriangle(int side1, int side2, int side3);
	float triArea(int side1, int side2, int side3);
	void triangleAngles(int side1, int side2, int side3, float angles[]);
	char* isRectangle(int pointA[], int pointB[], int pointC[], int pointD[]);
	void sort4PointsXY(int points_x[], int points_y[], int sorted_x[], int sorted_y[]);
	void sort4PointsCCW(int points_x[], int points_y[], int sorted_points[]);
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestRectangle {
	TEST_CLASS(DeleteThis)
	{

	public:
		//need to adjust these randomized points to go to sort4PointsXY() and sort4PointsCCW() -DW
		// some variations will go to isRectangle with the expected sorted results in sorted_points[x] from sort4PointsCCW -DW
		// positive slope rectangle
		/*TEST_METHOD(isRectangle_slantedRectangle_001)
		{
			int points_X[4] = { 15, 3, 16, 2 };
			int points_Y[4] = { 19, 5, 6, 18 };
			int expected = 0;
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(isRectangle_slantedRectangle_002)
		{
			int points_X[4] = { 19, 10, 11, 18 };
			int points_Y[4] = { 3, 10, 2, 11 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(isRectangle_slantedRectangle_003)
		{
			int points_X[4] = { 7, 8, 10, 5 };
			int points_Y[4] = { 9, 14, 11, 12 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(IsRectangle_slantedRectangle_004)
		{
			int points_X[4] = { 23, 15, 18, 20 };
			int points_Y[4] = { 3, 5, 0, 8 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		*/// example of two coordinates at the same point 
		/* TEST_METHOD(rectangleSolver_slantedRectangle_005)
		{
			int points_X[4] = {13, 13, 17, 12};
			int points_Y[4] = {25, 25, 19, 20};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}


		TEST_METHOD(isRectangle_slantedRectangle_005)
		{
			int points_X[4] = { 15, 3, 13, 1 };
			int points_Y[4] = { 2, 0, 14, 12 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(isRectangle_slantedRectangle_006)
		{
			int points_X[4] = { 17, 20, 10, 13 };
			int points_Y[4] = { 10, 3, 7, 0 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(isRectangle_slantedRectangle_007)
		{
			int points_X[4] = { 9, 13, 15, 19 };
			int points_Y[4] = { 3, 0, 11, 8 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		TEST_METHOD(isRectangle_slantedRectangle_008)
		{
			int points_X[4] = { 16, 19, 16, 12 };
			int points_Y[4] = { 11, 0, 11, 4 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		// negative slope rectangle (3:1)
		TEST_METHOD(isRectangle_slantedRectangle_009)
		{
			int points_X[4] = { 23, 32, 29, 20 };
			int points_Y[4] = { 0, 3, 12, 9 };
			Assert::IsTrue(std::strcmp(isRectangle(points_X, points_Y), "Is a rectangle") == 0);
		}
		// slots for two extra tests
		/* TEST_METHOD(rectangleSolver_slantedRectangle_009)
		{
			int points_X[4] = { 23, 32, 29, 20 };
			int points_Y[4] = { 0, 12, 12, 9 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_010)
		{
			int points_X[4] = { 23, 32, 29, 20 };
			int points_Y[4] = { 0, 12, 12, 9 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}  */
		// rectangle : A(3,8), B(8,8), C(8,11), D(3,11)
		// : (8,11), (3,11), (3,8), (8,8)
		/*
		TEST_METHOD(rectangleSolver_axisAlignedRectangle_001)
		{
			int points_X[4] = {};
			int points_Y[4] = {};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 0);
		}
		TEST_METHOD(rectangleSolver_axisAlignedRectangle_002)
		{
			int points_X[4] = {};
			int points_Y[4] = {};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 0);
		}

		*/
	};
	//ALL TEST METHODS PASSED FOR SORT4POINTSXY -DW
	//tests all combinations of sorting arrangements (total 24/2 for unique combinations for points_x and points_y) -DW
	TEST_CLASS(SortedPointsXY) {


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
	TEST_CLASS(SortedPointsCW) {


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
		int expected[4] = { 0, 3, 1, 2 };
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
		int expected[4] = {  };
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
		int expected[4] = { 1, 2, 0, 3 };
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

	//real one
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
		int expected[4] = {  };
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
		int expected[4] = { 0, 2, 3, 1 };
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

		for (int x = 0; x < 4; x++) {

			Assert::IsTrue(strcmp(isRectangle(points_X, points_Y,
		}
	}

	TEST_METHOD(isRectangle_AxisAlignedRectangle_002)
	{
		int points_X[4] = { 46, 40, 40, 46 };
		int points_Y[4] = { 6, 16, 6, 16 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_AxisAlignedRectangle_003)
	{
		int points_X[4] = { 12, 6, 12, 6 };
		int points_Y[4] = { 2, 2, 8, 8 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_001)
	{
		int points_X[4] = { 15, 3, 16, 2 };
		int points_Y[4] = { 19, 5, 6, 18 };
		int sorted_points[4] = { 1, 2, 0, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_002)
	{
		int points_X[4] = { 19, 10, 11, 18 };
		int points_Y[4] = { 3, 10, 2, 11 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_003)
	{
		int points_X[4] = { 7, 10, 2, 15 };
		int points_Y[4] = { 9, 22, 14, 17 };
		int sorted_points[4] = { 0, 3, 1, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_004)
	{
		int points_X[4] = { 23, 15, 18, 20 };
		int points_Y[4] = { 3, 5, 0, 8 };
		int sorted_points[4] = { 2, 0, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_005)
	{
		int points_X[4] = { 7, 20, 14, 13 };
		int points_Y[4] = { 14, 3, 17, 0 };
		int sorted_points[4] = { 3, 1, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_006)
	{
		int points_X[4] = { 9, 13, 15, 19 };
		int points_Y[4] = { 3, 0, 11, 8 };
		int sorted_points[4] = { 1, 3, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_007)
	{
		int points_X[4] = { 38, 20, 35, 23 };
		int points_Y[4] = { 5, 9, 14, 0 };
		int sorted_points[4] = { 3, 0, 2, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_SlantedRectangle_008)
	{
		int points_X[4] = { 15, 10, 5, 10 };
		int points_Y[4] = { 5, 0, 5, 10 };
		int sorted_points[4] = { 1, 0, 3, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Is a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4DifferentPoints_Lines_001)
	{
		int points_X[4] = { 20, 15, 25, 10 };
		int points_Y[4] = { 15, 10, 20, 5 };
		int sorted_points[4] = { 3, 1, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 20, 20 };
		int points_Y[4] = { 15, 10, 25, 20 };
		int sorted_points[4] = { 1, 0, 3, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_2DifferentPoints_Lines_001)
	{
		int points_X[4] = { 25, 10, 25, 10 };
		int points_Y[4] = { 20, 5, 20, 5 };
		int sorted_points[4] = { 1, 3, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_2DifferentPoints_Lines_002)
	{
		int points_X[4] = { 20, 20, 5, 5 };
		int points_Y[4] = { 20, 20, 20, 20 };
		int sorted_points[4] = { 2, 3, 0, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}


	TEST_METHOD(isRectangle_TriangleDegenerate_001)
	{
		int points_X[4] = { 20, 15, 10, 30 };
		int points_Y[4] = { 15, 10, 5, 7 };
		int sorted_points[4] = { 2, 3, 0, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_TriangleDegenerate_002)
	{
		int points_X[4] = { 20, 15, 10, 5 };
		int points_Y[4] = { 15, 10, 5, 50 };
		int sorted_points[4] = { 2, 1, 0, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_4SamePoints)
	{
		int points_X[4] = { 24, 24, 24, 24 };
		int points_Y[4] = { 14, 14, 14, 14 };
		int sorted_points[4] = { 0, 1, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Parallelogram_001)
	{
		int points_X[4] = { 0, 15, 20, 5 };
		int points_Y[4] = { 0, 0, 10, 10 };
		int sorted_points[4] = { 0, 1, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Parallelogram_002)
	{
		int points_X[4] = { 6, 6, 14, 14 };
		int points_Y[4] = { 6, 16, 12, 22 };
		int sorted_points[4] = { 0, 2, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Kite_001)
	{
		int points_X[4] = { 19, 16, 16, 15 };
		int points_Y[4] = { 10, 9, 11, 10 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Kite_002)
	{
		int points_X[4] = { 13, 25, 16, 16 };
		int points_Y[4] = { 10, 10, 13, 7 };
		int sorted_points[4] = { 3, 1, 2, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}
	TEST_METHOD(isRectangle_Trapezium_001)
	{
		int points_X[4] = { 35, 15, 25, 35 };
		int points_Y[4] = { 20, 5, 20, 10 };
		int sorted_points[4] = { 1, 3, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Trapezium_002)
	{
		int points_X[4] = { 15, 15, 0, 5 };
		int points_Y[4] = { 0, 5, 0, 5 };
		int sorted_points[4] = { 2, 0, 1, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IsocelesTrapezium_001)
	{
		int points_X[4] = { 25, 10, 15, 10 };
		int points_Y[4] = { 20, 5, 20, 15 };
		int sorted_points[4] = { 1, 0, 2, 3 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IsocelesTrapezium_002)
	{
		int points_X[4] = { 3, 6, 1, 7 };
		int points_Y[4] = { 4, 3, 3, 1 };
		int sorted_points[4] = { 3, 1, 0, 2 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}
	TEST_METHOD(isRectangle_IrregularParallelogram_001)
	{
		int points_X[4] = { 10, 20, 15, 11 };
		int points_Y[4] = { 10, 15, 5, 14 };
		int sorted_points[4] = { 2, 1, 3, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_IrregularParallelogram_002)
	{
		int points_X[4] = { 3, 6, 2, 7 };
		int points_Y[4] = { 4, 3, 2, 2 };
		int sorted_points[4] = { 2, 3, 1, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Concave_001)
	{
		int points_X[4] = { 4, 5, 7, 8 };
		int points_Y[4] = { 10, 9, 9, 4 };
		int sorted_points[4] = { 3, 2, 1, 0 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}

	TEST_METHOD(isRectangle_Concave_002)
	{
		int points_X[4] = { 9, 12, 11, 8 };
		int points_Y[4] = { 7, 12, 11, 12 };
		int sorted_points[4] = { 0, 2, 3, 1 };

		Assert::IsTrue(strcmp(isRectangle(points_X, points_Y, sorted_points), "Not a Rectangle") == 0);
	}




	};
	TEST_CLASS(RectanglePerimeter) {


public:

	};
	TEST_CLASS(RectangleArea) {


public:

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