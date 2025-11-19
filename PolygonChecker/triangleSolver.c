#include <stdio.h>
#include <stdbool.h>

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
float triArea(int a[], int b[], int c[]) {}
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



