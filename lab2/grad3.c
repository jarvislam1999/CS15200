#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab2.h"

void grad2(uint w, uint h, struct rgb c1, struct rgb c2);

void grad3(uint w, uint h, struct rgb c1, struct rgb c2, struct rgb c3);

void ppmcreateg3(uint w, uint h, struct rgb c1, struct rgb c2, struct rgb c3);


void ppmcreateg3(uint w, uint h, struct rgb c1, struct rgb c2, struct rgb c3) {
  // Actual function to print ppm content in main()
  fprintf(stdout, "P3 \n");
  fprintf(stdout, "%d %d \n", w, h);
  fprintf(stdout, "%d \n", 255);
  grad3(w, h, c1, c2, c3);
};


void grad2(uint w, uint h, struct rgb c1, struct rgb c2) {
  /* 
     I used the same grad2() function from grad2.c here
     Ideally, I would have included grad2() in a header function but 
     for the purpose of grading I believe just copy/paste it here would be 
     better. I reused grad2() since it would make grad3() much simpler
  */

  // Declaring increment steps for the three color channels
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


void grad3(uint w, uint h, struct rgb c1, struct rgb c2, struct rgb c3) {
  // Divide the width into half and apply grad2 on each half
  uint w1 = w/2;
  uint w2 = w - w1;
  // Print out the ppm pixels using grad2()
  for (int i = 0; i < h; ++i) {
    grad2(w1, 1, c1, c2);
    grad2(w2, 1, c2, c3);
  };
};


int main(){
  // For testing purpose
  ppmcreateg3(500, 50, RED, GREEN, BLUE);
}
