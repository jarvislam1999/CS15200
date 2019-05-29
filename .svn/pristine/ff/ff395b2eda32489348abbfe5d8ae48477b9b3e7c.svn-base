#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab2.h"
  
void grad2(uint w, uint h, struct rgb c1, struct rgb c2);

void ppmcreateg2(uint w, uint h, struct rgb c1, struct rgb c2);


void ppmcreateg2(uint w, uint h, struct rgb c1, struct rgb c2) {
  // Actual function to print ppm content in main()
  fprintf(stdout, "P3 \n");
  fprintf(stdout, "%d %d \n", w, h);
  fprintf(stdout, "%d \n", 255);
  grad2(w, h, c1, c2);
};

void grad2(uint w, uint h, struct rgb c1, struct rgb c2) {
  // Helper function to print out the pixel content
  // Determine increment step for the three color channels
  double step_r = (c2.r - c1.r)/((double)w);
  double step_g = (c2.g - c1.g)/((double)w);
  double step_b = (c2.b - c1.b)/((double)w);

  // Print out the ppm pixels
  for (int j = 0; j < h; j+=1){
    double r1 = (double) c1.r;
    double g1 = (double) c1.g;    
    double b1 = (double) c1.b;
    for (int i = 0; i < w; i+=1) {
      fprintf(stdout, "%d %d %d \n", (int) r1, (int) g1, (int) b1);
      r1 += step_r;
      g1 += step_g;
      b1 += step_b;
    };
  };
};


int main() {
  //Testing grad2()
  ppmcreateg2(500, 50, GREEN, BLUE);
  return 0;
};
