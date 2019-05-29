#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hsqueeze(int r1, int g1, int b1, int r2, int g2, int b2) {
  // Step to squeeze 2 consecutive pixels and print out one single pixel
  fprintf(stdout, "%d %d %d \n", (r1 + r2)/2, (g1 + g2)/2, (b1 + b2)/2);
  return;
};


int main() {
  char buffer[20] = {0};
  int w, h, d, r1, g1, b1, r2, g2, b2;
  fscanf(stdin,"%s",buffer);
  if (strcmp(buffer,"P3")!=0) {
    fprintf(stderr, "Error: File not PPM since P3 was not read \n");
    fprintf(stderr, 
	    "Will assume it's spelling error and proceed cautiously\n");
  };

  //Print out file header
  fprintf(stdout, "P3 \n");
  if (fscanf(stdin,"%d %d",&w,&h)!=2) {
    fprintf(stderr, 
	    "Error: Failed to get width and height, terminate program now \n");
    return 0;
  };

  //Print out width and height
  if (w <= 0 || h <= 0) {
    fprintf(stderr, 
	    "Error: Width or height not positive, terminate program now \n");
    return 0;
  };
  fprintf(stdout, "%d %d  \n", w/2, h);

  //Print out image depth
  if (fscanf(stdin,"%d",&d)!=1) {
    fprintf(stderr, "Error: Fail to fetch depth of image pixel, terminate \n");
    return 0;
  } else if (d!=255) {
    fprintf(stderr, "Warning: Image depth not 255, will print original\n");
  };

  fprintf(stdout, "%d \n", d);

  // For loop to print out pixel
  for (int i = 0; i < h; ++i){
    for (int j = 0; j < ((w % 2 == 0) ? (w) : w -1); j+=2){
      // Check if pixel values are valid
      if (fscanf(stdin,"%d %d %d",&r1,&g1,&b1) !=3){
	fprintf(stdout, "Warning: less than 3 ints were read for pixel\n");
      } else if (r1 < 0 || g1 < 0 || b1 < 0 || r1 > d || g1 > d || b1 > d){
	fprintf(stdout, "Warning: invalid values read for pixel\n");
      };
      if (fscanf(stdin,"%d %d %d",&r2,&g2,&b2) !=3){
	fprintf(stdout, "Warning: less than 3 ints were read for pixel\n");
      } else if (r2 < 0 || g2 < 0 || b2 < 0 || r2 > d || g2 > d || b2 > d){
	fprintf(stdout, "Warning: invalid values read for pixel\n");
      };
      // Print out pixel value
      hsqueeze(r1, g1, b1, r2, g2, b2);
    };
  };


  return 0;
};
