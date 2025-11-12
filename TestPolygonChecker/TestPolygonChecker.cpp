#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestPolygonChecker
{
	TEST_CLASS(rectangleSolver)
	{
		
	public:
		// positive slope rectangle
		TEST_METHOD(rectangleSolver_slantedRectangle_001)
		{
			int points_X[4] = {15, 3, 16, 2};
			int points_Y[4] = {19, 5, 6, 18};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_002)
		{ 
			int points_X[4] = {19, 10, 11, 18};
			int points_Y[4] = {3, 10, 2, 11};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_003)
		{
			int points_X[4] = {7, 8, 10, 5};
			int points_Y[4] = {9, 14, 11, 12};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_004)
		{
			int points_X[4] = {23, 15, 18, 20};
			int points_Y[4] = {3, 5, 0, 8};
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
			int points_X[4] = {15, 3, 13, 1};
			int points_Y[4] = {2, 0, 14, 12};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_006)
		{
			int points_X[4] = {17, 20, 10, 13};
			int points_Y[4] = {10, 3, 7, 0};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_slantedRectangle_007)
		{
			int points_X[4] = {5, 13, 11, 19};
			int points_Y[4] = {5, 0, 13, 7};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		/* TEST_METHOD(rectangleSolver_slantedRectangle_009)
		{
			int points_X[4] = {16, 19, 16, 12};
			int points_Y[4] = {11, 0, 11, 4};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		} */
		TEST_METHOD(rectangleSolver_slantedRectangle_008)
		{
			int points_X[4] = {23, 32, 29, 20};
			int points_Y[4] = {0, 12, 12, 9};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
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
		TEST_METHOD(rectangleSolver_axisAlignedRectangle_011)
		{
			int points_X[4] = {23, 32, 29, 20};
			int points_Y[4] = {0, 12, 12, 9};
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
		TEST_METHOD(rectangleSolver_axisAlignedRectangle_011)
		{
			int points_X[4] = { 23, 32, 29, 20 };
			int points_Y[4] = { 0, 12, 12, 9 };
			Assert::IsTrue(isRectangle(points_X, points_Y) == 1);
		}
	};
}
