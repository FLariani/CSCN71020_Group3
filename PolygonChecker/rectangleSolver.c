#include <stdio.h>
#include <stdbool.h>

#include "rectangleSolver.h"
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