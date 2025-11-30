/*#include <stdio.h>
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

*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "triangleSolver.h"
#include "rectangleSolver.h"

// Function prototypes -FL
void printWelcome(void);
void printShapeMenu(int* shapeChoice);
void getTriangleSides(int triangleSides[3]);
void getRectanglePoints(int points_x[4], int points_y[4]);
void handleTriangle(void);
void handleRectangle(void);

// helper to flush leftover characters from stdin -FL
void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // throw away -FL
    }
}

int main(void) {
    bool continueProgram = true;

    while (continueProgram) {
        printWelcome();

        int shapeChoice = -1;
        printShapeMenu(&shapeChoice);

        switch (shapeChoice) {
        case 1:
            handleTriangle();
            break;

        case 2:
            handleRectangle();
            break;

        case 0:
            continueProgram = false;
            printf("Exiting program.\n");
            break;

        default:
            // should not really happen because printShapeMenu checks -FL
            printf("Invalid value entered.\n\n");
            break;
        }
    }

    return 0;
}

// Menu and input functions -FL

void printWelcome(void) {
    printf("\n");
    printf(" Polygon Checker \n");
    printf("-----------------\n\n");
}

//asks until user enters 0, 1, or 2 and a real number -FL
void printShapeMenu(int* shapeChoice) {
    int scanned = 0;

        printf("Choose a shape:\n");
        printf("1. Triangle:\n");
        printf("2. Rectangle:\n");
        printf("0. Exit\n");
        printf("Enter number: ");

        scanned = scanf_s("%d", shapeChoice);
        clearInputBuffer();
        if (scanned != 1) {
            printf("Invalid input. Please enter 0, 1, or 2.\n\n");
            
            *shapeChoice = -1;   // force repeat -FL
        }    
}

// reads 3 sides, but repeats if the user types something non-numeric -FL
void getTriangleSides(int triangleSides[3]) {
    int scanned;

    printf("Enter the three sides of the triangle:\n");
    for (int i = 0; i < 3; i++) {
        do {
            printf("Side %d: ", i + 1);
            scanned = scanf_s("%d", &triangleSides[i]);
            clearInputBuffer();
            if (scanned != 1) {
                printf("Invalid input. Please enter a number.\n");
                
            }
        } while (scanned != 1);

    }
}

// reads 4 points, each as two ints; repeats if input is bad -FL
void getRectanglePoints(int points_x[4], int points_y[4]) {
    int scanned;

    printf("Enter 4 points as x y:\n");
    for (int i = 0; i < 4; i++) {
        do {
            printf("Point %d (x y): ", i + 1);
            scanned = scanf_s("%d %d", &points_x[i], &points_y[i]);
            clearInputBuffer();
            if (scanned != 2) {
                printf("Invalid input. Please enter two integers like: 0 2\n");
                
            }
        } while (scanned != 2);

    }
}

// Triangle workflow -FL

void handleTriangle(void) {
    int triangleSides[3] = { 0, 0, 0 };
    getTriangleSides(triangleSides);

    char* type = analyzeTriangle(triangleSides[0],
        triangleSides[1],
        triangleSides[2]);

    printf("\nTriangle type: %s\n", type);

    if (strcmp(type, "Not a triangle") != 0) {
        float angles[3] = { 0.0f, 0.0f, 0.0f };
        triangleAngles(triangleSides[0],
            triangleSides[1],
            triangleSides[2],
            angles);

        if (angles[0] < 0 || angles[1] < 0 || angles[2] < 0) {
            printf("Could not compute angles.\n\n");
            return;
        }

        float sum = angles[0] + angles[1] + angles[2];
        printf("Angles in degrees:\n");
        printf("A = %.2f\n", angles[0]);
        printf("B = %.2f\n", angles[1]);
        printf("C = %.2f\n", angles[2]);
        printf("Sum = %.2f\n\n", sum);
    }
}

// Rectangle workflow -FL

void handleRectangle(void) {
    int px[4], py[4];
    int order[4];

    getRectanglePoints(px, py);

    // order points counter-clockwise -FL
    sort4PointsCCW(px, py, order);

    // build A B C D arrays -FL
    int A[2] = { px[order[0]], py[order[0]] };
    int B[2] = { px[order[1]], py[order[1]] };
    int C[2] = { px[order[2]], py[order[2]] };
    int D[2] = { px[order[3]], py[order[3]] };

    // perimeter always -FL
    double perimeter = shapePerimeter(A, B, C, D);
    printf("\nPerimeter: %.2lf\n", perimeter);

    // rectangle check -FL
    char* rectResult = isRectangle(px, py, order);

    if (strcmp(rectResult, "Is a rectangle") == 0) {
        double area = RectArea(A, B, C);
        printf("This shape is a rectangle.\n");
        printf("Area: %.2lf\n\n", area);
    }
    else {
        printf("This shape is not a rectangle.\n\n");
    }
}

