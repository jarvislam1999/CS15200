#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"


// ... p3 code and p3 helper code here ...


unsigned char get_next_number(int *opt_char){
  // Get the next number from the buffer/ input file
  // We assume the buffer input would be positive number less than 256,
  // otherwise function behavior undefined
  
  int opt_char_convert = *opt_char - '0';  // Extract number out of ASCII code
  unsigned char output = 0;
  
  while (*opt_char < 48 || *opt_char > 57){ // While opt_char not a number
    *opt_char = getchar();
    opt_char_convert = *opt_char - '0';
  };
  while (*opt_char >= 48 && *opt_char <= 57 && *opt_char != EOF){
    output = output * 10 + (unsigned char)opt_char_convert;// Adding each digit
    (*opt_char) = getchar();
    opt_char_convert = *opt_char - '0';
  };
  
  return output;
};


unsigned short int get_next_height_width(int *opt_char){
  // Get the height and width from the buffer/ input file, same logic as above
  
  int opt_char_convert = *opt_char - '0';
  unsigned short int output = 0;
  while (*opt_char < 48 || *opt_char > 57){   // If opt_char not number
    *opt_char = getchar();
    opt_char_convert = *opt_char - '0';
  };  
  while (*opt_char >= 48 && *opt_char <= 57 && *opt_char != EOF){
    output = output * 10 + (unsigned short int)opt_char_convert;
    (*opt_char) = getchar();
    opt_char_convert = *opt_char - '0';
  };
  
  return output;
};


struct ppm *p3() {
  // Function to create out ppm file from the input file
  unsigned short int width;
  unsigned short int height;
  int opt_char;
  int *opt_char_ptr = &opt_char;
  
  // Print out P3 here since it will be in the output anyway
  // Undefined behaviour if input does not start with P3
  opt_char = getchar();   // Print out P
  putchar(opt_char);
  opt_char = getchar();   // Print out 3
  putchar(opt_char);
  opt_char = getchar();   // Print out whitespace
  putchar(opt_char);

  // Getting width and height from input file and allocate memory
  width = get_next_height_width(opt_char_ptr);
  height = get_next_height_width(opt_char_ptr);
  size_t pixel_array_size = sizeof(unsigned char) * 3
    * (int)width * (int)height;  // Size of pixels_
  
  struct rgb *pixels_ = (struct rgb *)malloc(pixel_array_size);
  struct ppm *output = (struct ppm *)malloc(pixel_array_size +
  			      sizeof(unsigned short int) * 2
  			      + sizeof(unsigned char));
  // Get color depth (255)
  unsigned char color_depth = get_next_number(opt_char_ptr);

  // Fill in the pixels
  int index = 0;                // To track index of pixels
  while (opt_char != EOF) {
    // Guard against white space at the end
    while (opt_char == ' ' || opt_char == '\n' || opt_char == '\t'){
      opt_char = getchar();      // reads character from stdin
    };
    if (opt_char == EOF)     // end of file
      break;

    //Insert pixels
    pixels_[index].r = get_next_number(opt_char_ptr);
    pixels_[index].g = get_next_number(opt_char_ptr);
    pixels_[index].b = get_next_number(opt_char_ptr);
    index += 1;
  };
  output->width = width;
  output->height = height;
  output->color_depth = color_depth;
  output->pixels = pixels_;
  return output;
};
  

int main()
{
  struct ppm *m = p3();

  // ... loop(s) to write horizontally-mirrored image to stdout ...
  // Print out width and height
  fprintf(stdout, "%hu %hu\n", m->width, m->height);
  fprintf(stdout, "%d \n", m->color_depth);

  // Print out pixels in reflected order
  for (int h = 0; h < m->height; h++) {
    for (int w = m->width - 1; w > -1; w--) {
      struct rgb pixel_out = m->pixels[h * m->width + w];
      fprintf(stdout, "%d %d %d \n", pixel_out.r,
      	      pixel_out.g, pixel_out.b);
    };
  };
  
  free(m->pixels);
  free(m);
  return 0;   
}
