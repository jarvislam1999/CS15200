#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab2.h"

void circle(uint side);

double distance(uint i1, uint j1, uint i2, uint j2);

double distance(uint i1, uint j1, uint i2, uint j2) {
  // Return Euclidean distance between two points in Cartesian coordinates
  return sqrt(pow((double)i1 - (double)i2, 2) + pow((double)j1 - (double)j2, 2));
};

void circle(uint side) {
  // Print out header for ppm file
  fprintf(stdout, "P3 \n");
  fprintf(stdout, "%d %d \n", side, side);
  fprintf(stdout, "%d \n", 255);

  // Calculate radius for our circle and the coordinates for its center
  double radius = ((double)side)/2.0;
  uint center = (int)radius;

  // Print out ppm pixels
  for (uint i = 0; i < side; ++i) {
    for (uint j = 0; j < side; ++j) {
      // Print black pixel if distance to center to is close to radius,
      if (fabs(distance(i, j, center, center) - radius) <= 1) {
	fprintf(stdout, "%d %d %d \n", BLACK.r, BLACK.g, BLACK.b);
      }
      else { // Print white pixel otherwise
	fprintf(stdout, "%d %d %d \n", WHITE.r, WHITE.g, WHITE.b);
      };
    };
  };
};

int main() {
  // Test for circle()
  circle(100);
};
