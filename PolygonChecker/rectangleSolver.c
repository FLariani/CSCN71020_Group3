#include <stdio.h>
#include <stdbool.h>

#include "rectangleSolver.h"

char* isRectangle(int pointA1, int pointA2, int pointB1, int pointB2, int pointC1, int pointC2, int pointD1, int pointD2) {
	char* result = "";
	
	if (pointA1 - pointB1 == pointC2 - pointB2 == pointD1 - pointC1 == pointD2 - pointA2)
	{
		result = "This is a rectangle!";
	} else if (pointA1 - pointB1 == pointC2 - pointB2 == pointD1 - pointC1 == pointD2 - pointA2)
	{
		result = "This is a rectangle!";
	}

	return result;
}