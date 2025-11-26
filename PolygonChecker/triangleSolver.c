#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "triangleSolver.h"

char* analyzeTriangle(int side1, int side2, int side3) {

	// 1. Invalid sides -FL
	if (side1 <= 0 || side2 <= 0 || side3 <= 0)
		return "Not a triangle";

	// 2. Triangle inequality test -FL
	if (side1 + side2 <= side3 ||
		side1 + side3 <= side2 ||
		side2 + side3 <= side1)
		return "Not a triangle";

	// 3. All sides equal -FL
	if (side1 == side2 && side2 == side3)
		return "Equilateral triangle";

	// 4. Exactly two sides equal -FL
	if (side1 == side2 || side1 == side3 || side2 == side3)
		return "Isosceles triangle";

	// 5. All sides different -FL
	return "Scalene triangle";
}


//find  the area of a triangle given point abc
// Find the area of a triangle given its 3 side lengths
float triangleArea(int side1, int side2, int side3)
{
	// If not a valid triangle, return -1 -FL
	if (side1 <= 0 || side2 <= 0 || side3 <= 0)
		return -1;

	// Triangle inequality check -FL
	if (side1 + side2 <= side3 ||
		side1 + side3 <= side2 ||
		side2 + side3 <= side1)
		return -1;

	// Convert to float for safety -FL
	float a = (float)side1;
	float b = (float)side2;
	float c = (float)side3;

	// Heron's formula -FL
	float s = (a + b + c) / 2.0f;           // semi-perimeter (following the formula) -Fl
	float areaSquared = s * (s - a) * (s - b) * (s - c);

	if (areaSquared <= 0)
		return -1;

	// square root -FL
	float area = sqrtf(areaSquared);

	return area;
}


float triArea(int a[], int b[], int c[]) {
	float x1 = a[0], y1 = a[1];
	float x2 = b[0], y2 = b[1];
	float x3 = c[0], y3 = c[1];

	float area = 0.5f * fabsf(
		x1 * (y2 - y3) +
		x2 * (y3 - y1) +
		x3 * (y1 - y2)
	);

	return area;
}


// a, b, c are points {x, y} -FL
// angles[0] = angle at point A -FL
// angles[1] = angle at point B -FL
// angles[2] = angle at point C -FL

void triangleAngles(int side1, int side2, int side3, float angles[]) {

	// Validate sides -FL
	if (side1 <= 0 || side2 <= 0 || side3 <= 0 ||
		side1 + side2 <= side3 ||
		side1 + side3 <= side2 ||
		side2 + side3 <= side1)
	{
		angles[0] = angles[1] = angles[2] = -1.0f;
		return;
	}

	// Convert to float for safety -FL
	float a = (float)side1;
	float b = (float)side2;
	float c = (float)side3;

	// Law of Cosines -Fl
	float A = acosf((b * b + c * c - a * a) / (2 * b * c));
	float B = acosf((a * a + c * c - b * b) / (2 * a * c));
	float C = acosf((a * a + b * b - c * c) / (2 * a * b));

	// Convert radians to degrees -FL
	const float PI = 3.1415926535f;
	angles[0] = A * (180.0f / PI);
	angles[1] = B * (180.0f / PI);
	angles[2] = C * (180.0f / PI);
}


//check if point p is in triangle abc
int pointIsInTri(int a[], int b[], int c[], int p[]) {
	float mainTri = triArea(a, b, c);
	float triNoA = triArea(p, b, c);
	float triNoB = triArea(a, p, c);
	float triNoC = triArea(a, b, p);
	float sumTriNoabc = triNoA + triNoB + triNoC;
	if (mainTri == sumTriNoabc) {
		return 1;
	}
	else {
		return 0;
	}

}



