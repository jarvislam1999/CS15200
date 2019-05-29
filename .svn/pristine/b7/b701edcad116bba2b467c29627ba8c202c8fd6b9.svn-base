#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Not enough or too many arguments!");
    return 0;
  };
  int bright_num = atoi(argv[1]);
  char buffer[20] = {0};
  int w, h, d, r, g, b;
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
  fprintf(stdout, "%d %d  \n", w, h);

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
    for (int j = 0; j < w; j++){
      // Check if pixel values are valid
      if (fscanf(stdin,"%d %d %d",&r,&g,&b) !=3){
	fprintf(stdout, "Warning: less than 3 ints were read for pixel\n");
      } else if (r < 0 || g < 0 || b < 0 || r > d || g > d || b > d){
	fprintf(stdout, "Warning: invalid values read for pixel\n");
      };

      // Print out pixel value
      fprintf(stdout, "%d %d %d \n", (r+ bright_num <=255)?r + bright_num: 255,
	      (g+ bright_num <=255)?g + bright_num: 255,
	      (b+ bright_num <=255)?b + bright_num: 255);
      };
  };


  return 0;
};
