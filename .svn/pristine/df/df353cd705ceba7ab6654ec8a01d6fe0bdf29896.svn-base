#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vsqueeze(int r1, int g1, int b1, int r2, int g2, int b2) {
  // Step to squeeze 2 consecutive pixels and print out one single pixel
  fprintf(stdout, "%d %d %d \n", (r1 + r2)/2, (g1 + g2)/2, (b1 + b2)/2);
  return;
};


int main() {
  char buffer[20] = {0};
  int w = 0; int h = 0; int d = 0;
  int r = 0;
  int g = 0;
  int b = 0;
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
  fprintf(stdout, "%d %d  \n", w, h/2);

  //Print out image depth
  if (fscanf(stdin,"%d",&d)!=1) {
    fprintf(stderr, "Error: Fail to fetch depth of image pixel, terminate \n");
    return 0;
  } else if (d!=255) {
    fprintf(stderr, "Warning: Image depth not 255, will print original\n");
  };

  fprintf(stdout, "%d \n", d);
  
  int pixels_r[w];
  int pixels_g[w];
  int pixels_b[w];
  // For loop to print out pixel
  for (int i = 0; i < ((h % 2 == 0) ? (h) : h - 1); i+=2){
    for (int j = 0; j < w; j++){
      // Check if pixel values are valid
      if (fscanf(stdin,"%d %d %d",pixels_r + j,
		 pixels_g + j, pixels_b + j) != 3){
	fprintf(stdout, "Warning: less than 3 ints were read for pixel\n");
      } else if (*(pixels_r + j) < 0 || *(pixels_g + j) < 0 
		 || *(pixels_b + j) < 0 || *(pixels_r + j) > d 
		 || *(pixels_g + j) > d || *(pixels_b + j) > d){
	fprintf(stdout, "Warning: invalid values read for pixel\n");
      };
    };
    // Print out pixel value
    for (int j = 0; j < w; j++){
      // Check if pixel values are valid
      if (fscanf(stdin,"%d %d %d",&r, &g, &b) != 3){
	fprintf(stdout, "Warning: less than 3 ints were read for pixel\n");
      } else if (r < 0 || g < 0 || b < 0 || r > d 
		 || g > d || b > d){
	fprintf(stdout, "Warning: invalid values read for pixel\n");
      };
      vsqueeze(r, g, b, *(pixels_r + j), *(pixels_g + j), *(pixels_b + j));
    };
  };


  return 0;
};
