#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "rectangleSolver.h"
#include "triangleSolver.h"
//swaps the indexs of a value
void swapper(int i, int j, int Array[]) {
	int hold = Array[j];
	Array[j] = Array[i];
	Array[i] = hold;
}
//swap values at index logic from of the first array from smallest# to bigest#,
//if it's tied sort the ties by bigest# to smallest# of the second array - JW 
void sortLowToHigh(int arrayOne[], int arrayTwo[], int arraySize) {
	for (int i = 0; i < arraySize; i++) {

		// j=i since we already made the first index the lowest we dont have to check again
		for (int j = i; j < arraySize; j++) {

			//if next index is bigger
			if (arrayOne[i] > arrayOne[j]) {

				//swap the position of x's is that index is smaller
				swapper(i, j, arrayOne);
				//mirror the swap
				swapper(i, j, arrayTwo);
			}
			//if the next element checked is the same swap it base on if y is bigger
			if (arrayOne[i] == arrayOne[j]) {
				if (arrayTwo[i] > arrayTwo[j]) {
					swapper(i, j, arrayOne);
					swapper(i, j, arrayTwo);
				}
			}
		}
	}
}
//print point:originally did this with loop, then realized i could use a single print statement
void printPoint(int point[]) {
	printf("(%d,%d) ", point[0], point[1]);
}
//print the array passed
void printArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	//printf("\n");
}
//finds if three in a row in a sorted function
int isThreeInRow(int array[]) {
	//if the index 2 apart are the same the one between is also same since its sorted
	if (array[0] == array[2] || array[1] == array[4]) {
		printf("\nthree points share an axis, its not a rectangle\n");
		return 1;
	}
	else {
		return 0;
	}
}
//finds distance between two points
float dOfPoints(int pointP[], int pointQ[]) {
	int deltaX = pointP[0] - pointQ[0];
	int deltaY = pointP[1] - pointQ[1];
	float distance = sqrtf((powf((float)deltaX, 2)) + (powf((float)deltaY, 2)));
	return distance;
}
//check if index of an array 0=1 or 2=3
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
char* isRectangles(int pointA1, int pointA2, int pointB1, int pointB2, int pointC1, int pointC2, int pointD1, int pointD2) {
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




int findArrowCase(int arrayXs[], int arrayYs[]) {
	int pointA[2];
	int pointB[2];
	int pointC[2];
	int pointD[2];
	pointA[0] = arrayXs[0];
	pointA[1] = arrayYs[0];
	pointB[0] = arrayXs[1];
	pointB[1] = arrayYs[1];
	pointC[0] = arrayXs[2];
	pointC[1] = arrayYs[2];
	pointD[0] = arrayXs[3];
	pointD[1] = arrayYs[3];
	int isBInC = pointIsInTri(pointA, pointC, pointD, pointB);
	int isCInB = pointIsInTri(pointA, pointB, pointD, pointD);
	if (isBInC == 1 || isCInB == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// takes the 4 points and returns the perimeter, assumes points are connected so a->b->c->d->a
float shapePerimeter(int PointA[], int PointB[], int PointC[], int PointD[]) {
	float sum = 0;
	sum += dOfPoints(&PointA, &PointB);
	sum += dOfPoints(&PointB, &PointC);
	sum += dOfPoints(&PointC, &PointD);
	sum += dOfPoints(&PointD, &PointA);
	return sum;
}
//area
float RectArea(int PointA[], int PointB[], int PointC[], int PointD[]) {
	float Area = 0;
	float sideA = dOfPoints(&PointA, &PointB);
	float sideB = dOfPoints(&PointA, &PointB);
	Area = sideA * sideB;
	return Area;
}



//ok the working ordering function for the 4 points outputs an indexes (a,b,c,d)
// before that, need to sort points lowest to highest y and x value with sort4PointsXY

void sort4PointsXY(int points_x[], int points_y[], int sorted_x[], int sorted_y[]) {

	
	//initializes original index order of points_x[] and points_y to be swapped
	for (int i = 0; i < 4; i++) {

		sorted_x[i] = i;
		sorted_y[i] = i;
	}

	for (int i = 0; i < 3; i++) {

		for (int j = i + 1; j < 4; j++) {

			if (points_x[sorted_x[i]] > points_x[sorted_x[j]]) {

				int temp = sorted_x[i];
				sorted_x[i] = sorted_x[j];
				sorted_x[j] = temp;
			}

			if (points_y[sorted_y[i]] > points_y[sorted_y[j]]) {

				int temp = sorted_y[i];
				sorted_y[i] = sorted_y[j];
				sorted_y[j] = temp;
			}
		}
	}
}

void sort4PointsCCW(int points_x[], int points_y[], int sorted_points[]) {

	int sorted_x[4] = { -1,-1,-1,-1 };
	int sorted_y[4] = { -1,-1,-1,-1 };

	sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

	//sorted_points[0] is the lowest y value out of the whole points_y[] using the sorted_y index
	//if there are ties then it finds the lowest x value out of points_x[] index match in sorted_x
	//sorted_points[0] is equivalent to Point A's index
	sorted_points[0] = sorted_y[0];
	for (int i = 1; i < 4; i++) {

		if (points_y[sorted_y[i]] < points_y[sorted_points[0]] ||
			(points_y[sorted_y[i]] == points_y[sorted_points[0]] && points_x[sorted_y[i]] < points_x[sorted_points[0]])) {

			sorted_points[0]= sorted_y[i];
		}
	}

	//creates a boolean check for usable indexes
	int used_points[4] = { 0,0,0,0 };


	if (sorted_points[0] >= 0 && sorted_points[0] <= 3) {

		used_points[sorted_points[0]] = 1;
	}

	//works as an index of sorted_x (output)
	//the smaller value of an index, the smaller the x-value of that points_x's index
	//the element index of position_sorted_x is the same as points_x translated into sorted_x's translation of points_x
	int position_sorted_x[4] = { -1,-1,-1,-1 };
	for (int x = 0; x < 4; x++) {

		if (sorted_points[x] >= 0 && sorted_points[x] <= 3) {

			position_sorted_x[sorted_x[x]] = x;
		}
	}

	//find sorted_points[1], [2], [3] by smallest angle
	//angle is determined by dx and dy relative to sorted_points[0] or point A
	//use sorted_x as a tie-breaker for cross==0
	for (int point_letter = 1; point_letter < 4; point_letter++) {

		int next_point = -1;

		for (int i = 0; i < 4; i++) {

			//skips used points_x and points_y index if used already in a sorted point
			if (used_points[i]) {

				continue;
			}

			//wad
			if (next_point == -1) {

				next_point = i;
				continue;
			}

			double dx1 = (double)points_x[i] - points_x[sorted_points[0]];
			double dy1 = (double)points_y[i] - points_y[sorted_points[0]];
			double dx2 = (double)points_x[next_point] - points_x[sorted_points[0]];
			double dy2 = (double)points_y[next_point] - points_y[sorted_points[0]];

			double cross = dy1 * dx2 - dy2 * dx1;

			//cross has negative values indicate that next_point is the next clockwise point compared to i
			if (cross < 0) {

				next_point = i;
			}

			//cross has a value of 0 when both i and next_point are colinear to point A (or sorted_points[0]
			else if (cross == 0) {

				// for collinear use sorted_x position as tie-break (lowest x-value)
				if (position_sorted_x[i] < position_sorted_x[next_point]) {

					next_point = i;
				}
			}
			
		}

		sorted_points[point_letter] = next_point;
		used_points[next_point] = 1;

	}
}

char* isRectangle(int pointA[],int pointB[],int pointC[],int pointD[]) {

	//we can make a function to do some of this stuff
	float a_b_x = pointB[0] - pointA[0];
	float a_b_y = pointB[1] - pointA[1];

	float a_d_x = pointD[0] - pointA[0];
	float a_d_y = pointD[1] - pointA[1];

	float b_a_x = pointA[0] - pointB[0];
	float b_a_y = pointA[1] - pointB[1];

	float b_c_x = pointC[0] - pointB[0];
	float b_c_y = pointC[1] - pointB[1];

	float c_b_x = pointB[0] - pointC[0];
	float c_b_y = pointB[1] - pointC[1];

	float c_d_x = pointD[0] - pointC[0];
	float c_d_y = pointD[1] - pointC[1];

	float d_c_x = pointC[0] - pointD[0];
	float d_c_y = pointC[1] - pointD[1];

	float d_a_x = pointA[0] - pointD[0];
	float d_a_y = pointA[1] - pointD[1];

	float ab_dot_ad = (a_b_x * a_d_x) + (a_b_y * a_d_y);
	float ba_dot_bc = (b_a_x * b_c_x) + (b_a_y * b_c_y);
	float cb_dot_cd = (c_b_x * c_d_x) + (c_b_y * c_d_y);
	float dc_dot_da = (d_c_x * d_a_x) + (d_c_y * d_c_y);

	if ((ab_dot_ad + ba_dot_bc + cb_dot_cd + dc_dot_da) == 0) {

		return "Is a rectangle";
	}

	else {

		return "Not a rectangle";
	}
}

/* //or
char* isRectangle(int points_x[], int points_y[], int sorted_points[]) {

	for (int x = 0; x < 4; x++) {

		int nextPoint;
		int prevPoint;

		if (x + 1 == 4) {

			nextPoint = sorted_points[0];
		}

		else {

			nextPoint = sorted_points[x + 1];
		}

		if (x - 1 == -1) {

			prevPoint = sorted_points[3];
		}

		else {

			prevPoint = sorted_points[x - 1];
		}
		
		float nextDeltaX = points_x[nextPoint] - points_x[sorted_points[x]];
		float nextDeltaY = points_y[nextPoint] - points_y[sorted_points[x]];
		float prevDeltaX = points_x[prevPoint] - points_x[sorted_points[x]];
		float prevDeltaY = points_y[prevPoint] - points_y[sorted_points[x]];

		if (((nextDeltaX * prevDeltaX) + (nextDeltaY * prevDeltaY)) != 0) {

			return "Not a rectangle";
		}
	}

	return "Is a rectangle";
}

//its about the same amount of lines
*/