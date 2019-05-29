#include<stdio.h>
#include<math.h>

typedef unsigned int uint;

// We define bool to follow the code logic more easily
typedef int bool;
#define true 1
#define false 0

struct point {
  double x;
  double y;
};

struct circle {
  struct point c;
  double r;
};

// An axis_box has sides parallel to the x- and y-axis.
// The width and the height must be nonnegative.
struct axis_box {
  struct point upper_left;
  double width;
  double height;
};

//Helper function to find distance between 2 points
double distance(struct point p, struct point q);

// Return true if the circles share no points in common.
int disjoint(struct circle c1, struct circle c2);

// Return true if the the first circle, c1, entirely contains
// the second circle.
int contains(struct circle c1, struct circle c2);

// A polygon is represented as an array of points. The
// points are arranged in clockwise order. Among the
// line segments described, there are no crossings or
// backtrackings along segments. The initial point
// does not appear redundantly as the last point in
// the array; it is assumed the last explicit point
// is connected back to the first one.
// If the array of points given is not at least three
// items long, or if the other properties are
// violated, the behavior of the function is undefined.
double poly_perim(struct point *points, uint len);

// Function to find the maximum/ minimum point
double opt_point(struct circle *circles, uint min, uint n, uint len);

// Compute the smallest axis-aligned bounding box that contains
// all the given circles. It is acceptable for the circles to
// touch the box. If the array given is of length 0, the
// behavior of the function is undefined.
struct axis_box bounding_box(struct circle *circles, uint len);

// Return true if (a,b,c) is a Pythagorean triple.
// Assume a,b,c are positive, and c is the largest.
// If these properties are not adhered to, the behavior
// of the function is undefined.
int pythag(uint a, uint b, uint c);

// Return true only if a, b, and c form a triangle.
int triangle(struct point a, struct point b, struct point c);

// Count the number of 0 bits in the given unsigned long int.
uint num_zeros(unsigned long int n);

// Count the number of 1 bits in the given unsigned long int.
uint num_ones(unsigned long int n);

// Print the given number as a string of binary digits to stdout.
// Its length should be as long as is the bit length of an unsigned
// long int on the current computer, including leading zeros.
// Recall you can use sizeof to compute the length of a type in bytes.
// The "largest bit" must appear first, and there must be a space
// between every four bits for ease of reading. Print a newline
// character after printing all bits. 
void show_binary(unsigned long int n);



