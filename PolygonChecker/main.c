#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "triangleSolver.h"
#include "rectangleSolver.h"

int main() {
	bool continueProgram = true;
	while (continueProgram) {
		printWelcome();

		int shapeChoice = -1;
		printShapeMenu(&shapeChoice);

		switch (shapeChoice)
		{
		case 1:
			printf_s("Triangle selected.\n");
			int triangleSides[3] = { 0, 0, 0 };
			getTriangleSides(triangleSides);
			char* result = analyzeTriangle(triangleSides[0], triangleSides[1], triangleSides[2]);
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

void printShapeMenu(int *shapeChoice) {
	printf_s("1. Triangle\n");
	printf_s("0. Exit\n");

	//cannot take an input of 9 or it breaks the code (change to %d) -DW
	//fgets is better to restrict user 
	//ie. fgets()
	printf_s("Enter number: ");
	scanf_s("%1o", &(*shapeChoice));
}

void getTriangleSides(int* triangleSides) {
	printf_s("Enter the three sides of the triangle: ");
	for (int i = 0; i < 3; i++)
	{
		scanf_s("%d", &triangleSides[i]);
	}
}