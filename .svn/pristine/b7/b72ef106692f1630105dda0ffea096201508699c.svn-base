#include<stdio.h>
#include "hw1.h"


// Function implementation here
double distance(struct point p, struct point q){
  // Calculate the Euclidean distance between any two points
  return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2)); // Positive value
};


int disjoint(struct circle c1, struct circle c2) {
  // Return true if two circles are disjoint
  if (distance(c1.c,c2.c) <= c1.r + c2.r){
    return false;
  }
  else{
    return true;
  };
};


int contains(struct circle c1, struct circle c2){
  // Return true if the first circle contains the second one
  if (distance(c1.c,c2.c) <= c1.r - c2.r){
    return true;
  }
  else{
    return false;
  };
};


double poly_perim(struct point *points, uint len){
  // Calculate the perimeter of a polygon
  double sum = 0;
  for (int i = 0; i < len - 1; i++){
    sum += distance(*(points + i),*(points + i + 1));
  };
  sum += distance(*(points), *(points + len - 1));
  return sum;
};


// Complicated function to aid bounding_box()
double opt_point(struct circle *circles, uint min, uint n, uint len) {
  // Calculate the max/min of the circle center and radius
  // If min == True then calculate min, if n == False calculate max
  // If n == True then calculate x, if n == False calculate y
  // It could have been cleaner but I did not want to introduce more functions
  double out;
  if (n == true) {                // Min of circle.c.x
    if (min == true){
      out = circles->c.x - circles->r;
      for (int i = 1; i < len; i++) {
	if (out > (circles + i)->c.x - (circles + i)->r) {
	  out = (circles + i)->c.x - (circles + i)->r;
	};
      };
    };
    if (min == false){           // Max of circle.c.x
      out = (circles)->c.x + (circles)->r;
      for (int i = 1; i < len; i++) {
	if (out < (circles + i)->c.x + (circles + i)->r) {
	  out = (circles + i)->c.x + (circles + i)->r;
	};
      };
    };
  };

  if (n == false) {              // Min of circle.c.y
    if (min == true){
      out = (circles)->c.y - (circles)->r;
      for (int i = 1; i < len; i++) {
	if (out > (circles + i)->c.y - (circles + i)->r) {
	  out = (circles + i)->c.y - (circles + i)->r;
	};
      };
    };
    if (min == false){          // Max of circle.c.y
      out = (circles)->c.y + (circles)->r;
      for (int i = 1; i < len; i++) {
	if (out < (circles + i)->c.y + (circles + i)->r) {
	  out = (circles + i)->c.y + (circles + i)->r;
	};
      };
    };
  };
  return out;
};


struct axis_box bounding_box(struct circle *circles, uint len){
  // Return the bounding box for an array of circles
  double x0 = opt_point(circles, true, true, len);  // Bottom-left corner x
  double y0 = opt_point(circles, true, false, len); // Bottom-left corner y
  double x1 = opt_point(circles, false, true, len); // Upper right corner x
  double y1 = opt_point(circles, false, false, len);// Upper right corner y
  struct axis_box out = {{x0, y0}, x1 - x0, y1 -y0}; // Our desired output
  return out;
};


int pythag(uint a, uint b, uint c){
  // Return True if the three numbers are Pythagorean numbers
  if (pow(a, 2) + pow(b, 2) == pow(c, 2)){
    return true;
  }
  else {
    return false;
  };
};


int triangle(struct point a, struct point b, struct point c) {
  // Return True if a, b, c form a triangle
  double area = 0.5 * (a.x * (b.y - c.y) + b.x * (c.y -a.y) +
		       c.x * (a.y - b.y));
  if (area == 0) {
    return false;
  }
  else {
    return true;
  };
};


uint num_zeros(unsigned long int n) {
  // Return number of zeroes in bit of n
  // Referenced online source for inspiration
  // https://stackoverflow.com/questions/4244274/how-do-i-count-the-number-of-zero-bits-in-an-integer
  size_t num_zeros_ = 0;
  for(size_t i = 0; i < sizeof(unsigned long int) * 8; i++, n >>= 1)
    {
      if ((n & 1) == 0)
	num_zeros_ ++;
    }
  return num_zeros_;
};


uint num_ones(unsigned long int n) {
  // Return number of ones in bit of n
  size_t num_ones_ = 0;
  for(size_t i = 0; i < sizeof(unsigned long int) * 8; i++, n >>= 1)
    {
      if ((n & 1) != 0)
	num_ones_ ++;
    }
  return num_ones_;
};


void show_binary(unsigned long int n){
  // Print out the binary form of a number
  fprintf(stdout, "%lu =", n);

  for(size_t i = 0; i < sizeof(unsigned long int) * 8; i++, n <<= 1)
    {
      unsigned long int m = 1;
      m <<= (sizeof(unsigned long int) * 8 - 1);
      if (i % 4 == 0){
	fprintf(stdout, " ");
      };
      if ((n & m) != 0){
	fprintf(stdout, "%d", 1);
      }
      else {
	fprintf(stdout, "%d", 0);
      };
    }
  fprintf(stdout, "\n");
  return ;
};



int main()
{
  // Test for disjoint()
  int flag = 0; // Check for violation
  struct circle c1 = {{1.,1.}, 1.};
  struct circle c2 = {{1.,1.}, 1.};
  if (disjoint(c1, c2) != false){
    fprintf(stdout, "disjoint({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected False \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    disjoint(c1,c2));
    flag = 1;
  };
  c1.c.x = 1.; c1.c.y = 1.; c1.r = 1.;
  c2.c.x = 2.; c2.c.y = 2.; c2.r = 0.75;
  if (disjoint(c1, c2) != false){
    fprintf(stdout, "disjoint({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected False \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    disjoint(c1,c2));
    flag = 1;
  };
  c1.c.x = 1.; c1.c.y = 1.; c1.r = 2.5;
  c2.c.x = 4.; c2.c.y = 5.; c2.r = 2.5;
  if (disjoint(c1, c2) != false){
    fprintf(stdout, "disjoint({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected False \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    disjoint(c1,c2));
    flag = 1;
  };
  c1.c.x = 1.; c1.c.y = 1.; c1.r = 2.;
  c2.c.x = 10.; c2.c.y = 8.; c2.r = 4;
  if (disjoint(c1, c2) != true){
    fprintf(stdout, "disjoint({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected True \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    disjoint(c1,c2));
    flag = 1;
  };
  // Print message if no error
  if (flag == 0){
    fprintf(stdout, "disjoint() works as expected! \n");
  };


  
  // Test for contains()
  flag = 0; // Check for violation

  c1.c.x = 1.; c1.c.y = 1.; c1.r = 1.;
  c2.c.x = 1.; c2.c.y = 1.; c2.r = 1.;
  if (contains(c1, c2) != true){
    fprintf(stdout, "contains({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected True \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    contains(c1,c2));
    flag = 1;
  };
  c1.c.x = 8.; c1.c.y = 8.; c1.r = 5.;
  c2.c.x = 8.; c2.c.y = 8.; c2.r = 2.75;
  if (contains(c1, c2) != true){
    fprintf(stdout, "contains({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected True \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    contains(c1,c2));
    flag = 1;
  };
  c1.c.x = 8.; c1.c.y = 8.; c1.r = 5.;
  c2.c.x = 6.; c2.c.y = 6.; c2.r = 1;
  if (contains(c1, c2) != true){
    fprintf(stdout, "contains({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected True \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    contains(c1,c2));
    flag = 1;
  };
  c1.c.x = 1.; c1.c.y = 1.; c1.r = 2.;
  c2.c.x = 10.; c2.c.y = 8.; c2.r = 4;
  if (contains(c1, c2) != false){
    fprintf(stdout, "contains({{%f,%f}, %f}, {{%f,%f}, %f} yielded %d, \\
expected False \n", c1.c.x, c1.c.y, c1.r, c2.c.x, c2.c.y, c2.r,
	    contains(c1,c2));
    flag = 1;
  };
  // Print message if no error
  if (flag == 0){
    fprintf(stdout, "contains() works as expected! \n");
  };


  
  // Test for poly_perim()
  flag = 0;
  struct point points[5] = {{1., 1.}, {1., 2.}, {2., 2.},
			    {2., 1.}, {1., 1.}};
  struct point *p;
  p = points;
  if (poly_perim(p, 4) != 4.0) {
     fprintf(stdout, "poly_perim for {{%f,%f}, {%f,%f}, {%f,%f}, {%f,%f}} yielded %f, expected %f \n", points[0].x, points[0].y, points[1].x,
	     points[1].y, points[2].x, points[2].y, points[3].x, points[3].y,
	     poly_perim(p, 4), 4.);
     flag = 1;
  };
  points[0].x = 1.; points[0].y = 1.;
  points[1].x = 4.; points[1].y = 5.;
  points[2].x = 7.; points[2].y = 1.; 
  if (poly_perim(p, 3) != 16.0) {
     fprintf(stdout, "poly_perim for {{%f,%f}, {%f,%f}, {%f,%f}} yielded %f, expected %f \n", points[0].x, points[0].y, points[1].x,
	     points[1].y, points[2].x, points[2].y, poly_perim(p, 3), 16.0);
     flag = 1;
  };
  points[0].x = 1.; points[0].y = 1.;
  points[1].x = 1.; points[1].y = 5.;
  points[2].x = 4.; points[2].y = 9.;
  points[3].x = 7.; points[3].y = 5.;
  points[4].x = 4.; points[4].y = 1.; 
  if (poly_perim(p, 5) != 22.0) {
     fprintf(stdout, "poly_perim for {{%f,%f}, {%f,%f}, {%f,%f}, {%f,%f}, {%f, %f}} yielded %f, expected %f \n", points[0].x, points[0].y, points[1].x,
	     points[1].y, points[2].x, points[2].y, points[3].x, points[3].y,
	     points[4].x, points[4].y, poly_perim(p, 5), 22.0);
     flag = 1;
  };

  if (flag == 0){
    fprintf(stdout, "poly_perim() works as expected! \n");
  };


  // Test for bounding_box()
  flag = 0; // Check for violation
  struct circle circles[4] = {{{1.,1.}, 1.}, {{1.,1.}, 1.}, {{1.,1.}, 1.}, 
		       {{1.,1.}, 1.}};
  struct circle *ci = circles;
  struct axis_box b_box = {{0., 0.}, 2., 2.};
  struct axis_box b_box_expected = bounding_box(ci, 3);
  if (b_box.upper_left.x != b_box_expected.upper_left.x ||
      b_box.upper_left.y != b_box_expected.upper_left.y ||
      b_box.width != b_box_expected.width ||
      b_box.height != b_box_expected.height){
    fprintf(stdout, "bounding_box({{%f, %f}, %f}, {{%f, %f}, %f}, \\
{{%f, %f}, %f}) yielded {{%f, %f}, %f, %f}, expected {{%f, %f}, %f, %f} \n",
	    circles[0].c.x, circles[0].c.y, circles[0].r,
	    circles[1].c.x, circles[1].c.y, circles[1].r,
	    circles[2].c.x, circles[2].c.y, circles[2].r,
	    b_box.upper_left.x, b_box.upper_left.y,
	    b_box.width, b_box.height,
	    b_box_expected.upper_left.x, b_box_expected.upper_left.y,
	    b_box_expected.width, b_box_expected.height);
    flag = 1;
  };
  circles[0].c.x = 2.; circles[0].c.y = 2.; circles[0].r = 1.;
  circles[1].c.x = 15.; circles[1].c.y = 4.; circles[1].r = 2.;
  circles[2].c.x = 3.; circles[2].c.y = 10.; circles[2].r = 3.;
  circles[3].c.x = 8.; circles[3].c.y = 6.; circles[3].r = 2.;
  b_box.upper_left.x = 0.; b_box.upper_left.y = 1.;
  b_box.width = 17.; b_box.height = 12.;
  b_box_expected = bounding_box(ci, 4);
  if (b_box.upper_left.x != b_box_expected.upper_left.x ||
      b_box.upper_left.y != b_box_expected.upper_left.y ||
      b_box.width != b_box_expected.width ||
      b_box.height != b_box_expected.height){
    fprintf(stdout, "bounding_box({{%f, %f}, %f}, {{%f, %f}, %f}, \\
{{%f, %f}, %f}, {{%f, %f}, %f}) yielded {{%f, %f}, %f, %f}, \\
expected {{%f, %f}, %f, %f} \n",
	    circles[0].c.x, circles[0].c.y, circles[0].r,
	    circles[1].c.x, circles[1].c.y, circles[1].r,
	    circles[2].c.x, circles[2].c.y, circles[2].r,
	    circles[3].c.x, circles[3].c.y, circles[3].r,
	    b_box.upper_left.x, b_box.upper_left.y,
	    b_box.width, b_box.height,
	    b_box_expected.upper_left.x, b_box_expected.upper_left.y,
	    b_box_expected.width, b_box_expected.height);
    flag = 1;
  };

  if (flag == 0){
    fprintf(stdout, "bounding_box() works as expected!\n");
  };



  // Test for pythag()
  uint x, y, z;
  flag = 0;
  x = 3;
  y = 4;
  z = 5;
  if (pythag(x, y, z) != true){
    fprintf(stdout, "pythag(%d, %d, %d) yielded %d, \\
expected True \n", x, y, z, pythag(x, y, z));
    flag = 1;
  };
  x = 2;
  y = 3;
  z = 4;
  if (pythag(x, y, z) != false){
    fprintf(stdout, "pythag(%d, %d, %d) yielded %d, \\
expected False \n", x, y, z, pythag(x, y, z));
    flag = 1;
  };
  x = 5;
  y = 5;
  z = 5;
  if (pythag(x, y, z) != false){
    fprintf(stdout, "pythag(%d, %d, %d) yielded %d, \\
expected False \n", x, y, z, pythag(x, y, z));
    flag = 1;
  };
  if (flag == 0){
    fprintf(stdout, "pythag() works as expected!\n");
  };



  // Test for triangle()
  flag = 0;
  points[0].x = 1.; points[0].y = 1.;
  points[1].x = 2.; points[1].y = 2.;
  points[2].x = 3.; points[2].y = 3.;
  if (triangle(points[0], points[1], points[2]) != false){
    fprintf(stdout, "triangle({%f,%f}, {%f,%f}, {%f,%f}) yielded %d, \\
expected False \n", points[0].x, points[0].y, points[1].x,
	    points[1].y, points[2].x, points[2].y,
	    triangle(points[0], points[1], points[2]));
    flag = 1;
  };
  points[0].x = 1.; points[0].y = 1.;
  points[1].x = 1.; points[1].y = 2.;
  points[2].x = 1.; points[2].y = 3.;
  if (triangle(points[0], points[1], points[2]) != false){
    fprintf(stdout, "triangle({%f,%f}, {%f,%f}, {%f,%f}) yielded %d, \\
expected False \n", points[0].x, points[0].y, points[1].x,
	    points[1].y, points[2].x, points[2].y,
	    triangle(points[0], points[1], points[2]));
    flag = 1;
  };
  points[0].x = 1.; points[0].y = 1.;
  points[1].x = 2.; points[1].y = 2.;
  points[2].x = 3.; points[2].y = 5.;
  if (triangle(points[0], points[1], points[2]) != true){
    fprintf(stdout, "triangle({%f,%f}, {%f,%f}, {%f,%f}) yielded %d, \\
expected True \n", points[0].x, points[0].y, points[1].x,
	    points[1].y, points[2].x, points[2].y,
	    triangle(points[0], points[1], points[2]));
    flag = 1;
  };

  if (flag == 0){
    fprintf(stdout, "triangle() works as expected!\n");
  };


  // Test for num_zeros()
  flag = 0;
  unsigned long int q;
  q = 12076;
  if ((unsigned long int)num_zeros(q) != sizeof(unsigned long int) * 8 - 8) {
    fprintf(stdout, "num_zeros(%lu) yielded %d, expected %lu \n",
	    q, num_zeros(q), sizeof(unsigned long int) * 8 - 8);
    flag = 1;
  };
  q = 999999999;
  if ((unsigned long int)num_zeros(q) != sizeof(unsigned long int) * 8- 21) {
    fprintf(stdout, "num_zeros(%lu) yielded %d, expected %lu \n",
	    q, num_zeros(q), sizeof(unsigned long int) * 8 - 21);
    flag = 1;
  };
  q = 0;
  if ((unsigned long int)num_zeros(q) != sizeof(unsigned long int) * 8) {
    fprintf(stdout, "num_zeros(%lu) yielded %d, expected %lu \n",
	    q, num_zeros(q), sizeof(unsigned long int) * 8);
    flag = 1;
  };
  if (flag == 0){
    fprintf(stdout, "num_zeros() works as expected!\n");
  };


  // Test for num_ones()
  flag = 0;

  q = 35345;
  if ((unsigned long int)num_ones(q) != 5) {
    fprintf(stdout, "num_ones\(%lu) yielded %d, expected %d \n",
	    q, num_ones(q), 5);
    flag = 1;
  };
  q = 888888888;
  if ((unsigned long int)num_ones(q) != 18) {
    fprintf(stdout, "num_ones(%lu) yielded %d, expected %d \n",
	    q, num_ones(q), 18);
    flag = 1;
  };
  q = 0;
  if ((unsigned long int)num_ones(q) != 0) {
    fprintf(stdout, "num_ones(%lu) yielded %d, expected %d \n",
	    q, num_ones(q), 0);
    flag = 1;
  };
  if (flag == 0){
    fprintf(stdout, "num_ones() works as expected!\n");
  };



  // Print out show_binary
  fprintf(stdout, "Testing show_binary() \n");
  q = 123456;
  show_binary(q);
  q = 777777777;
  show_binary(q);
  q = 0;
  show_binary(q);
  q = 987654;
  show_binary(q);

  return 0;
}
