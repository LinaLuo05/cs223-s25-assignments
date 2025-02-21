/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 20, 2025
 * Description: takes a PPM image as a command line argument and displays it as ASCII Art.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char *argv[]){
  if (argc != 2) {
    printf("Usage: %s <PPM filename>\n", argv[0]);
    return 1;
  }

  char* filename = argv[1]; 
  int w, h;
  struct ppm_pixel* pixels = read_ppm(filename, &w, &h);

  printf("Reading %s with width %d and height %d\n", filename, w, h);
  for (int i = 0 ; i < h; i++){
    for (int j = 0; j < w; j++){
      float intensity = (1.0/3.0) * (pixels[i*w + j].red + pixels[i*w + j].green + pixels[i*w + j].blue);
      if (intensity < 26) {
        printf("@");
      } 
      else if (intensity >= 26 && intensity < 51) {
        printf("#");
      } 
      else if (intensity >= 51 && intensity < 76) {
        printf("%%");
      } 
      else if (intensity >= 76 && intensity < 101) {
        printf("*");
      } 
      else if (intensity >= 101 && intensity < 126) {
        printf("o");
      } 
      else if (intensity >= 126 && intensity < 151) {
        printf(";");
      } 
      else if (intensity >= 151 && intensity < 176) {
        printf(":");
      } 
      else if (intensity >= 176 && intensity < 201) {
        printf(",");
      } 
      else {
        printf(" ");
      }
    }
    printf("\n");
  }

  free(pixels);

  return 0;
}
