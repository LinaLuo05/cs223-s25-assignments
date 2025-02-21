/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 20, 2025
 * Description: reads in a PPM file and "glitches" it, then store it 
 * in a new file with suffix "-glitch". 
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct ppm_pixel* glitch(struct ppm_pixel* image, int w, int h) {
  struct ppm_pixel* glitched_image = malloc(sizeof(struct ppm_pixel) * w * h);
  for (int i = 0; i < (h); i++) {
    for (int j = 0; j < (w); j++) {
      glitched_image[i*w+j].red   = (image[i*w+j].red << (rand() % 2));
      glitched_image[i*w+j].green = (image[i*w+j].green << (rand() % 2));
      glitched_image[i*w+j].blue  = (image[i*w+j].blue << (rand() % 2));
    }
  }
  return glitched_image;
  free(glitched_image);
}


int main(int argc, char *argv[]){
  if (argc != 2) {
    printf("Usage: %s <PPM filename>\n", argv[0]);
    return 1;
  }
  char* filename = argv[1]; 
  int w, h;
  //reading in the file
  struct ppm_pixel* pixels = read_ppm(filename, &w, &h);
  printf("Reading %s with width %d and height %d\n", filename, w, h);

  //calling the function to write glitched outfile 
  struct ppm_pixel* glitched_pixels = glitch(pixels, w, h);

  //creating the outfile name with suffix "-glitch.ppm"
  char outfileName[256];
  int i;
  for (i = 0; i < strlen(filename) - 4; i++) {
      outfileName[i] = filename[i];
  }
  outfileName[i] = '\0';
  strcat(outfileName, "-glitch.ppm");

  //write the glitched image into binary file
  write_ppm(outfileName,glitched_pixels,w,h);
  printf("Writing file %s\n", outfileName);

  free(pixels);
  free(glitched_pixels);
  
  return 0;
}
