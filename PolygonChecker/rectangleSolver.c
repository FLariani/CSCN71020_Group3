#include <stdio.h>
#include <stdbool.h>

#include "rectangleSolver.h"
/*swaps the indexs of a value*/
void swapper(int i, int j, int Array[]) {
	int hold = Array[j];
	Array[j] = Array[i];
	Array[i] = hold;
}
/*swap values at index logic from of the first array from smallest# to bigest#,
if it's tied sort the ties by bigest# to smallest# of the second array - JW */
void sortLowToHigh(int arrayOne[], int arrayTwo[], int arraySize) {
	for (int i = 0; i < arraySize; i++) {

		/* j=i since we already made the first index the lowest we dont have to check again*/
		for (int j = i; j < arraySize; j++) {

			/*if next index is bigger*/
			if (arrayOne[i] > arrayOne[j]) {

				/*swap the position of x's is that index is smaller*/
				swapper(i, j, arrayOne);
				/*mirror the swap*/
				swapper(i, j, arrayTwo);
			}
			/*if the next element checked is the same swap it base on if y is bigger*/
			if (arrayOne[i] == arrayOne[j]) {
				if (arrayTwo[i] > arrayTwo[j]) {
					swapper(i, j, arrayOne);
					swapper(i, j, arrayTwo);
				}
			}
		}
	}
}
/*print point:originally did this with loop, then realized i could use a single print statement*/
void printPoint(int point[]) {
	printf("(%d,%d) ", point[0], point[1]);
}
/*print the array passed*/
void printArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	//printf("\n");
}
/* finds if three in a row in a sorted function*/
int isThreeInRow(int array[]) {
	/*if the index 2 apart are the same the one between is also same since its sorted*/
	if (array[0] == array[2] || array[1] == array[4]) {
		printf("\nthree points share an axis, its not a rectangle\n");
		return 1;
	}
	else {
		return 0;
	}
}
/*finds distance between two points*/
float dOfPoints(int pointP[], int pointQ[]) {
	int deltaX = pointP[0] - pointQ[0];
	int deltaY = pointP[1] - pointQ[1];
	float distance = sqrtf((powf((float)deltaX, 2)) + (powf((float)deltaY, 2)));
	return distance;
}
/*check if index of an array 0=1 or 2=3*/
int isLineOnAxis(int array[]) {
	if ((array[0] == array[1]) || (array[2] == array[4])) {
		if ((array[0] == array[1]) || (array[2] == array[4])) {
			return 2;
		}
		else {
			return 1;
		}

	}
	else {
		return 0;
	}
}
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


#include <stdio.h>

int isRectangle(int points_X[], int points_Y[]) {

	int max_Y = points_Y[0];
	int min_Y = points_Y[0];
	int max_X = points_X[0];
	int min_X = points_X[0];
	int counter_Xmin = 0;
	int counter_Xmax = 0;
	int counter_Ymin = 0;
	int counter_Ymax = 0;
	int min_Xpoint[2] = { 0, -1 };
	int max_Xpoint[2] = { 0, -1 };
	int min_Ypoint[2] = { 0, -1 };
	int max_Ypoint[2] = { 0, -1 };
	int pointA[2] = { -1, -1 };
	int pointB[2] = { -1, -1 };
	int pointC[2] = { -1, -1 };
	int pointD[2] = { -1, -1 };
	int map[4] = { -1,-1,-1,-1 }; // add in next iteration

	//gets rid of duplicate points
	for (int x = 0; x < y; x++) {

		for (int y = 3; y > x; y--) {

			if ((points_X[x] == points_X[y]) && (points_Y[x] == points_Y[y])) {

				printf("Not a rectangle");
				return 0;
			}
		}

	}

	for (int x = 1; x < 4; x++) {

		if (points_X[x] <= min_X) {

			counter_Xmin++;


			if (points_X[x] < min_X) {

				min_X = points_X[x];
				min_Xpoint[0] = x;
				min_Xpoint[1] = -1;
				counter_Xmin = 0;
			}

			else if (counter_Xmin == 1) {

				min_Xpoint[1] = x;
			}

			else {

				printf("Not a rectangle");
				return 0;
			}
		}

		if (points_X[x] >= max_X) {

			counter_Xmax++;

			if (points_X[x] > max_X) {

				max_X = points_X[x];
				max_Xpoint[0] = x;
				max_Xpoint[1] = -1;
				counter_Xmax = 0;
			}

			else if (counter_Xmax == 1) {

				max_Xpoint[1] = x;
			}

			else {

				printf("Not a rectangle");
				return 0;
			}
		}

		if (points_Y[x] <= min_Y) {
			counter_Ymin++;
			if (points_Y[x] < min_Y) {

				min_Y = points_Y[x];
				min_Ypoint[0] = x;
				min_Ypoint[1] = -1;
				counter_Ymin = 0;

			}

			else if (counter_Ymin == 1) {

				min_Ypoint[1] = x;

			}

			else {

				printf("Not a rectangle");
				return 0;
			}
		}

		if (points_Y[x] >= max_Y) {

			counter_Ymax++;

			if (points_Y[x] > max_Y) {

				max_Y = points_Y[x];
				max_Ypoint[0] = x;
				max_Ypoint[1] = -1;
				counter_Ymax = 0;
			}

			else if (counter_Ymax == 1) {

				max_Ypoint[1] = x;
			}

			else {

				printf("Not a rectangle");
				return 0;
			}
		}
	}

	//create the new points
	//return 1 for rectangles instead of break
	//get rid of while loop

	while (1) {
		//only allows rectangles now
		if (counter_Xmax + counter_Xmin + counter_Ymax + counter_Ymin == 4) {

			//check if the first min x point matches the first min y point for A point orientation (bottom left corner)
			if (min_Xpoint[0] == min_Ypoint[0]) {

				pointA[0] = points_X[min_Xpoint[0]];
				pointA[1] = points_Y[min_Xpoint[0]];
				pointB[0] = points_X[min_Ypoint[1]];
				pointB[1] = points_Y[min_Ypoint[1]];
				pointD[0] = points_X[min_Xpoint[1]];
				pointD[1] = points_Y[min_Xpoint[1]];

				//check if first max x point is the bottom right corner
				if (min_Ypoint[1] == max_Xpoint[0]) {

					pointC[0] = points_X[max_Xpoint[1]];
					pointC[1] = points_Y[max_Xpoint[1]];
					return 1;
				}

				//second max x point is bottom right corner
				else {

					pointC[0] = points_X[max_Xpoint[0]];
					pointC[1] = points_Y[max_Xpoint[0]];
					return 1;
				}
			}

			else {

				pointA[0] = points_X[min_Xpoint[1]];
				pointA[1] = points_Y[min_Xpoint[1]];
				pointB[0] = points_X[min_Ypoint[0]];
				pointB[1] = points_Y[min_Ypoint[0]];
				pointD[0] = points_X[min_Xpoint[0]];
				pointD[1] = points_Y[min_Xpoint[0]];

				if (min_Ypoint[1] == max_Xpoint[0]) {

					pointC[0] = points_X[max_Xpoint[1]];
					pointC[1] = points_Y[max_Xpoint[1]];
					return 1;
				}

				else {

					pointC[0] = points_X[max_Xpoint[0]];
					pointC[1] = points_Y[max_Xpoint[0]];
					return 1;
				}
			}

		}

		//gets rid of lines, Vs and more irredgular shapes before then next else if
		else if ((min_Xpoint[0] == max_Ypoint[0]) || (min_Xpoint[0] == min_Ypoint[0]) || (max_Xpoint[0] == max_Ypoint[0]) || (max_Xpoint[0] == min_Ypoint[0])) {

			printf("Not a rectangle");
			return 0;
		}

		//checks for unique man/min x/y value shapes
		else if (counter_Xmax + counter_Xmin + counter_Ymax + counter_Ymin == 0) {

			pointA[0] = points_X[min_Ypoint[0]];
			pointA[1] = points_Y[min_Ypoint[0]];
			pointB[0] = points_X[max_Xpoint[0]];
			pointB[1] = points_Y[max_Xpoint[0]];
			pointC[0] = points_X[max_Ypoint[0]];
			pointC[1] = points_Y[max_Ypoint[0]];
			pointD[0] = points_X[min_Xpoint[0]];
			pointD[1] = points_Y[min_Xpoint[0]];
			//more code here for rectangle distinction 
			//distance between corners D^2DB==D^2AC= ((Cy-Ay)^2 + (Cx-Ax)^2) == ((By-Dy)^2 + (Bx-Dx)^2)

			if (((pointC[1] - pointA[1]) * (pointC[1] - pointA[1]) + (pointC[0] - pointA[0]) * (pointC[0] - pointA[0])) == ((pointB[1] - pointD[1]) * (pointB[1] - pointD[1]) + (pointB[0] - pointD[0]) * (pointB[0] - pointD[0]))) {

				return 1;
			}

			else {

				return 0;
			}
		}

		else {
			printf("Not a rectangle");
			return 0;
		}
	}
}