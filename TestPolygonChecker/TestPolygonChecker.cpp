#include "pch.h"
#include "CppUnitTest.h"
extern "C" char* analyzeTriangle(int side1, int side2, int side3);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestPolygonChecker
{
	TEST_CLASS(rectangleSolver)
	{

	public:
		// positive slope rectangle
		TEST_METHOD(rectangleSolver_slantedRectangle_001)
		{
			int points_X[4] = { 15, 3, 16, 2 };
			int points_Y[4] = { 19, 5, 6, 18 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_002)
		{
			int points_X[4] = { 19, 10, 11, 18 };
			int points_Y[4] = { 3, 10, 2, 11 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_003)
		{
			int points_X[4] = { 7, 8, 10, 5 };
			int points_Y[4] = { 9, 14, 11, 12 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_004)
		{
			int points_X[4] = { 23, 15, 18, 20 };
			int points_Y[4] = { 3, 5, 0, 8 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		// example of two coordinates at the same point
		/* TEST_METHOD(rectangleSolver_slantedRectangle_005)
		{
			int points_X[4] = {13, 13, 17, 12};
			int points_Y[4] = {25, 25, 19, 20};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		} */
		TEST_METHOD(rectangleSolver_slantedRectangle_005)
		{
			int points_X[4] = { 15, 3, 13, 1 };
			int points_Y[4] = { 2, 0, 14, 12 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_006)
		{
			int points_X[4] = { 17, 20, 10, 13 };
			int points_Y[4] = { 10, 3, 7, 0 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_007)
		{
			int points_X[4] = { 5, 13, 11, 19 };
			int points_Y[4] = { 5, 0, 13, 7 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		 TEST_METHOD(rectangleSolver_slantedRectangle_009)
		{
			int points_X[4] = {16, 19, 16, 12};
			int points_Y[4] = {11, 0, 11, 4};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		} */
		// negative slope rectangle (3:1)
		TEST_METHOD(rectangleSolver_slantedRectangle_008)
		{
			int points_X[4] = {23, 26, 29, 20};
			int points_Y[4] = {0, 21, 12, 9};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
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

		TEST_METHOD(rectangleSolver_axisAlignedRectangle_001)
		{ 
			int points_X[4] = {};
			int points_Y[4] = {};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_axisAlignedRectangle_002)
		{
			int points_X[4] = {};
			int points_Y[4] = {};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
	}; 


	TEST_CLASS(TriangleTypeTests) {
public:

	TEST_METHOD(NotTriangle_ZeroOrNegative) {
		Assert::IsTrue(std::strcmp("Not a triangle", analyzeTriangle(0, 3, 4)) == 0);
		Assert::IsTrue(std::strcmp("Not a triangle", analyzeTriangle(-1, 3, 3)) == 0);
	}

	TEST_METHOD(Equilateral_333) {
		Assert::IsTrue(std::strcmp("Equilateral triangle", analyzeTriangle(3, 3, 3)) == 0);
	}

	TEST_METHOD(Isosceles_445) {
		Assert::IsTrue(std::strcmp("Isosceles triangle", analyzeTriangle(4, 4, 5)) == 0);
	}

	TEST_METHOD(Scalene_345) {
		Assert::IsTrue(std::strcmp("Scalene triangle", analyzeTriangle(3, 4, 5)) == 0);
	}
	};
}

