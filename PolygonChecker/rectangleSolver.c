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


int isRectangle(int points_X[], int points_Y[]) {

	int max_Y, min_Y = points_Y[0];
	int max_X, min_X = points_X[0];
	int counter_max, counter_min = 0;
	int min_point[2] = { 0, -1 };
	int max_point[2] = { 0, -1 };
	int pointA[2], pointB[2], pointC[2], pointD[2];
	int y_points[2];

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
		while (1) {

			if (counter_max + counter_min == 2) {

				if ((points_Y[min_point[0]] == points_Y[min_point[1]]) || (points_Y[max_point[0]] == points_Y[max_point[1]])) {

					printf("Not a rectangle");
					return 0;
				}

				if (points_Y[min_point[0]] == points_Y[max_point[0]]) {

					if ((points_Y[min_point[0]] < points_Y[min_point[1]]) && (points_Y[min_point[0]] < points_Y[max_point[1]])) {

						pointA[0] = points_X[min_point[0]];
						pointA[1] = points_Y[min_point[0]];
						pointB[0] = points_X[max_point[0]];
						pointB[1] = points_Y[max_point[0]];
						pointC[0] = points_X[max_point[1]];
						pointC[1] = points_Y[max_point[1]];
						pointD[0] = points_X[min_point[1]];
						pointD[1] = points_Y[min_point[1]];
						break;
					}

					else if ((points_Y[min_point[0]] > points_Y[min_point[1]]) && (points_Y[min_point[0]] > points_Y[max_point[1]])) {

						pointA[0] = points_X[min_point[1]];
						pointA[1] = points_Y[min_point[1]];
						pointB[0] = points_X[max_point[1]];
						pointB[1] = points_Y[max_point[1]];
						pointC[0] = points_X[max_point[0]];
						pointC[1] = points_Y[max_point[0]];
						pointD[0] = points_X[min_point[0]];
						pointD[1] = points_Y[min_point[0]];
						break;
					}
				}

				//need to fix later and then add one for counter_max +counter_min==0
				//else overall should be a return saying not a rectangle
				else if (points_Y[min_point[0]] == points_Y[max_point[1]]) {

					if ((points_Y[min_point[0]] < points_Y[min_point[1]]) && (points_Y[min_point[0]] < points_Y[max_point[0]])) {

						pointA[0] = points_X[min_point[0]];
						pointA[1] = points_Y[min_point[0]];
						pointB[0] = points_X[max_point[1]];
						pointB[1] = points_Y[max_point[1]];
						pointC[0] = points_X[max_point[0]];
						pointC[1] = points_Y[max_point[0]];
						pointD[0] = points_X[min_point[1]];
						pointD[1] = points_Y[min_point[1]];
						break;
					}

					else if ((points_Y[min_point[0]] < points_Y[min_point[1]]) && (points_Y[min_point[0]] < points_Y[max_point[0]])) {

						pointA[0] = points_X[min_point[1]];
						pointA[1] = points_Y[min_point[1]];
						pointB[0] = points_X[max_point[0]];
						pointB[1] = points_Y[max_point[0]];
						pointC[0] = points_X[max_point[1]];
						pointC[1] = points_Y[max_point[1]];
						pointD[0] = points_X[min_point[0]];
						pointD[1] = points_Y[min_point[0]];
						break;
					}
				}

				printf("Not a rectangle");
				return 0;
			}
			else if (counter_max + counter_min == 0) {

				pointB[0] = points_X[max_point[0]];
				pointB[1] = points_Y[max_point[0]];
				pointD[0] = points_X[min_point[0]];
				pointD[1] = points_Y[min_point[0]];

				int index_count = 0;

				for (int i = 0; i < 4; i++) {

					if ((i != max_point[0]) && (i != min_point[0])) {

						y_points[index_count] = i;
						++index_count;
					}
				}

				if (points_Y[y_points[0]] < points_Y[y_points[1]]) {

					pointA[0] = points_X[y_points[0]];
					pointA[1] = points_Y[y_points[0]];
					pointC[0] = points_X[y_points[1]];
					pointC[1] = points_Y[y_points[1]];
					break;
				}

				else if (points_Y[y_points[0]] > points_Y[y_points[1]]) {

					pointA[0] = points_X[y_points[1]];
					pointA[1] = points_Y[y_points[1]];
					pointC[0] = points_X[y_points[0]];
					pointC[1] = points_Y[y_points[0]];
					break;
				}

				else {

					printf("Not a rectangle");
					return 0;
				}
			}

			else {

				printf("Not a rectangle");
				return 0;
			}
		}
		//now you have point A to D coordinates

	}