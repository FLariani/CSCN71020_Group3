#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "triangleSolver.h"

char* analyzeTriangle(int side1, int side2, int side3) {
	char* result = "";
	if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
		result = "Not a triangle";
	}
	else if (side1 == side2 && side1 == side3) {
		result = "Equilateral triangle";
	}
	else if ((side1 == side2 && side1 != side3) || 
		(side1 == side3 && side1 != side2))
	{
		result = "Isosceles triangle";
	}
	else {
		result = "Scalene triangle";
	}

	return result;
}

//find  the area of a triangle given point abc


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

void triAngles(int a[], int b[], int c[], float angles[]) {
	// Side lengths using distance formula -FL
	float ab = sqrtf((b[0] - a[0]) * (b[0] - a[0]) +
		(b[1] - a[1]) * (b[1] - a[1]));

	float bc = sqrtf((c[0] - b[0]) * (c[0] - b[0]) +
		(c[1] - b[1]) * (c[1] - b[1]));

	float ca = sqrtf((a[0] - c[0]) * (a[0] - c[0]) +
		(a[1] - c[1]) * (a[1] - c[1]));

	// Law of Cosines for each angle -FL
	float A = acosf((ab * ab + ca * ca - bc * bc) / (2 * ab * ca));
	float B = acosf((ab * ab + bc * bc - ca * ca) / (2 * ab * bc));
	float C = acosf((bc * bc + ca * ca - ab * ab) / (2 * bc * ca));

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



