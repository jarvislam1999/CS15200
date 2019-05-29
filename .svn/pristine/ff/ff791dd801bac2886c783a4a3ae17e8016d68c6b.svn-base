#include <stdio.h>
#include <stdlib.h>

struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct ppm {
  unsigned short int width;
  unsigned short int height;
  unsigned char color_depth;
  struct rgb *pixels;
};

// read P3 file from stdin
struct ppm *p3();
