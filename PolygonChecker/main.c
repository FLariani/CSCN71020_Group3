#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "triangleSolver.h"

//global variable never used -DW
int side = 0;

int main() {
	bool continueProgram = true;
	while (continueProgram) {
		printWelcome();

		//could declare the integer and call at address -DW
		/* ie. int shapeChoice; -DW
		* printShapeMenu(&shapeChoice); -DW
		*/
		int shapeChoice = printShapeMenu();

		switch (shapeChoice)
		{
		case 1:
			printf_s("Triangle selected.\n");
			int triangleSides[3] = { 0, 0, 0 };
			//unnessary initialization int* triangleSides is the same -DW
			int* triangleSidesPtr = getTriangleSides(triangleSides);
			//printf_s("! %d\n", triangleSidesPtr[0]);
			//can use triangleSides instead of triangleSidesPtr -DW
			char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
			printf_s("%s\n", result);
			break;
		case 0:
			continueProgram = false;
			break;
		default:
			printf_s("Invalid value entered.\n");
			break;
		}
	}
	return 0;
}

void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}
//could use the shape choice declaration in the main() as a int* variable -DW
//make the function void -DW
int printShapeMenu() {
	printf_s("1. Triangle\n");
	printf_s("0. Exit\n");

	int shapeChoice;

	printf_s("Enter number: ");
	scanf_s("%1o", &shapeChoice);

	return shapeChoice;
}
//unnecessary pointer for return as the pointer triangleSides already returns the value to the caller variable -DW
//could be void instead of int* -DW
int* getTriangleSides(int* triangleSides) {
	printf_s("Enter the three sides of the triangle: ");
	for (int i = 0; i < 3; i++)
	{
		scanf_s("%d", &triangleSides[i]);
	}
	return triangleSides;
}