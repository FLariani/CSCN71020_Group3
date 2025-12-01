#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "rectangleSolver.h"
#include "triangleSolver.h"


//sorts points from lowest to highest value -DW
void sort4PointsXY(int points_x[], int points_y[], int sorted_x[], int sorted_y[]) {

	//initializes original index order of points_x[] and points_y to be swapped -DW
	for (int i = 0; i < 4; i++) {

		sorted_x[i] = i;
		sorted_y[i] = i;
	}
	
	for (int i = 0; i < 3; i++) {

		for (int j = i+1; j < 4; j++) {

			if (points_x[sorted_x[i]] >= points_x[sorted_x[j]]) {

				//checks when points are of equal value to switch to user's first input x-value -DW
				if ((sorted_x[i] < sorted_x[j]) && (points_x[sorted_x[i]] == points_x[sorted_x[j]])) {}
				else {

					int temp = sorted_x[i];
					sorted_x[i] = sorted_x[j];
					sorted_x[j] = temp;
				}
			}

			if (points_y[sorted_y[i]] >= points_y[sorted_y[j]]) {

				//checks when points are of equal value to switch to user's first input y-value -DW
				if ((sorted_y[i] < sorted_y[j]) && (points_y[sorted_y[i]] == points_y[sorted_y[j]])) {}
				else {
					int temp = sorted_y[i];
					sorted_y[i] = sorted_y[j];
					sorted_y[j] = temp;
				}
			}
		}
	}
}

//The ordering function for the 4 points outputs in indexes (a,b,c,d) -DW
// before that, we need to sort points lowest to highest y and x value with sort4PointsXY -DW
void sort4PointsCCW(int points_x[], int points_y[], int sorted_points[]) {

	int sorted_x[4] = { -1,-1,-1,-1 };
	int sorted_y[4] = { -1,-1,-1,-1 };

	sort4PointsXY(points_x, points_y, sorted_x, sorted_y);

	//sorted_points[0] is the lowest y value out of the whole points_y[] using the sorted_y index -DW
	//if there are ties then it finds the lowest x value out of points_x[] index match in sorted_x -DW
	//sorted_points[0] is equivalent to Point A's index -DW
	sorted_points[0] = sorted_y[0];
	for (int i = 1; i < 4; i++) {

		if (points_y[sorted_y[i]] < points_y[sorted_points[0]] ||
			(points_y[sorted_y[i]] == points_y[sorted_points[0]] &&
			 points_x[sorted_y[i]] < points_x[sorted_points[0]])) {

			sorted_points[0]= sorted_y[i];
		}
	}

	//creates a boolean check for usable indexes -DW
	int used_points[4] = { 0,0,0,0 };

	if (sorted_points[0] >= 0 && sorted_points[0] <= 3) {

		used_points[sorted_points[0]] = 1;
	}

	//works as an index of sorted_x (output) -DW
	//the smaller value of an index, the smaller the y-value of that points_y's index -DW
	//the element index of position_sorted_y is the same as points_y translated into sorted_y's translation of points_x -DW
	int position_sorted_y[4] = { -1,-1,-1,-1 };
	int position_sorted_x[4] = { -1,-1,-1,-1 };
	for (int x=0; x<4; x++) {

		if ((sorted_x[x] >= 0 && sorted_x[x] <= 3) && (sorted_y[x] >= 0 && sorted_y[x] <= 3)) {
		

			position_sorted_x[sorted_x[x]] = x;
			position_sorted_y[sorted_y[x]] = x;
		}
	}
	
	//used to determine ordering with colinear points
	int flag_colinear = -1;

	//find sorted_points[1], [2], [3] by smallest angle -DW
	//angle is determined by dx and dy relative to sorted_points[0] or point A -DW
	//use sorted_x as a tie-breaker for cross==0 -DW
	for (int point_letter = 1; point_letter < 4; point_letter++) {

		int next_point = -1;

		for (int i = 0; i < 4; i++) {

			//skips used points_x and points_y index if used already in a sorted point -DW
			if (used_points[i]) {

				continue;
			}

			//adds the first valid point available to be compared to a different valid point (continue) -DW
			if (next_point == -1) {

				next_point = i;
				continue;
			}

			long long dx1 = points_x[i] - points_x[sorted_points[0]];
			long long dy1 = points_y[i] - points_y[sorted_points[0]];
			long long dx2 = points_x[next_point] - points_x[sorted_points[0]];
			long long dy2 = points_y[next_point] - points_y[sorted_points[0]];

			long cross = dy1 * dx2 - dy2 * dx1;

			//cross has negative values indicate that next_point is the next clockwise point compared to i -DW
			if (cross < 0) {

				next_point = i;
			}

			//cross has a value of 0 when both i and next_point are colinear to point A (or sorted_points[0] -DW
			else if (cross == 0) {

				//if pointB was not colinear when C and D are -DW
				if (point_letter == 2 && flag_colinear != sorted_points[1]) {
					
					if (position_sorted_y[i] > position_sorted_y[next_point]) {

						next_point = i;
					}
				}
				else if (*(points_y+i) == *(points_y+next_point)) {

					if (position_sorted_x[i] < position_sorted_x[next_point]) {

						next_point = i;
					}
				}
				// for collinear use sorted_y position as tie-break (lowest y-value) -DW
				else if (position_sorted_y[i] < position_sorted_y[next_point]) {

					next_point = i;
				}

				flag_colinear = next_point;
			}
		}
		//adds the next coordinate to the next sorted points -DW
		//adds the next coordinate's index in points x and y to the used points -DW
		sorted_points[point_letter] = next_point;
		used_points[next_point] = 1;
	}
}
 //probably use this one because it has the ability to work with duplicate coordinates -DW
char* isRectangle(int points_x[], int points_y[], int sorted_points[]) {
	
	//each coordinate will be tested if dot product is 90 degrees
	for (int x = 0; x < 4; x++) {
	
		//next and previous ordered point for dot product -DW
		int nextPoint;
		int prevPoint;

		//if current coordinate is pointD then the next connected coordinate will be pointA -DW
		if (x + 1 == 4) {

			nextPoint = sorted_points[0];
		}
		else {

			nextPoint = sorted_points[x + 1];
		}

		//if current coordinate is pointA then the previous connected coordinate will be pointD -DW
		if (x - 1 == -1) {

			prevPoint = sorted_points[3];
		}
		else {

			prevPoint = sorted_points[x - 1];
		}
		
		//finds the translation of x and y between the tested cooordinate and the next or previous coordinate -DW
		long long nextDeltaX = points_x[nextPoint] - points_x[sorted_points[x]];
		long long nextDeltaY = points_y[nextPoint] - points_y[sorted_points[x]];
		long long prevDeltaX = points_x[prevPoint] - points_x[sorted_points[x]];
		long long prevDeltaY = points_y[prevPoint] - points_y[sorted_points[x]];

		//if dot product is not 0 then the angle is not 90 degrees -DW
		//if the delta X and Y between the coordinate being tested and the next/previous coodinate is 0 then it is a duplicate coordinate -DW
		if ((((nextDeltaX * prevDeltaX) + (nextDeltaY * prevDeltaY)) != 0)||
		((nextDeltaX==0)&&(nextDeltaY==0))||((prevDeltaX==0)&&(prevDeltaY==0))) {

			return "Not a rectangle";
		}
	}
	return "Is a rectangle";
}

//finds distance between two points
double dOfPoints(int pointP[], int pointQ[]) {
	double deltaX = pointQ[0] - pointP[0]  ;
	double deltaY = pointQ[1] - pointP[1];
	double distance = sqrtf((powf(deltaX, 2)) + (powf(deltaY, 2)));
	return distance;
}

// takes the 4 points and returns the perimeter, assumes points are connected so a->b->c->d->a
double shapePerimeter(int PointA[], int PointB[], int PointC[], int PointD[]) {
	double sum = 0;
	sum += dOfPoints(PointA, PointB);
	sum += dOfPoints(PointB, PointC);
	sum += dOfPoints(PointC, PointD);
	sum += dOfPoints(PointD, PointA);
	return sum;
}

//area
double RectArea(int PointA[], int PointB[], int PointC[]) {
	double Area = 0;
	double sideA = dOfPoints(PointA, PointB);
	double sideB = dOfPoints(PointB, PointC);
	Area = sideA * sideB;
	return Area;
}





