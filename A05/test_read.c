/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 20, 2025
 * Description: test case of read;
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // todo: print out the grid of pixels
  printf("Testing file feep-raw.ppm: %d %d\n",w, h );
  for (int i = 0 ; i < h; i++){
    for (int j = 0; j < w; j++){
      printf("(%d, %d, %d) ", pixels[i*w + j].red, 
      pixels[i*w + j].green, pixels[i*w + j].blue);
    }
    printf("\n");
  }


  free(pixels);
  return 0;
}

