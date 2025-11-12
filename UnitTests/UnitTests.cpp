#include "pch.h"
#include "CppUnitTest.h"
#include <cstring>  // strcmp
#include <math.h>   // fabs
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" 
    char* analyzeTriangle(int side1, int side2, int side3);

namespace TriangleTests
{

    TEST_CLASS(TriangleTypeTests)
    {
    public:

        TEST_METHOD(NotTriangle_ZeroOrNegative) {
            Assert::IsTrue(std::strcmp("Not a triangle", analyzeTriangle(0, 3, 4)) == 0);
            Assert::IsTrue(std::strcmp("Not a triangle", analyzeTriangle(-1, 3, 3)) == 0);
        }

        TEST_METHOD(NotTriangle_InequalityFails) {
            // 2 + 5 <= 8  not a triangle
            Assert::IsTrue(std::strcmp("Not a triangle", analyzeTriangle(2, 5, 8)) == 0);
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

