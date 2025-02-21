/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 20, 2005
 * Description: test case of write_ppm
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // test writing the file to test.ppm, reload it, and print the contents
  write_ppm("test.ppm", pixels, w, h);


  int w2, h2;
  struct ppm_pixel* pixel2 = read_ppm("test.ppm", &w2, &h2);
  printf("Testing file test.ppm: %d %d\n",w, h);
  for (int i = 0 ; i < h; i++){
    for (int j = 0; j < w; j++){
      printf("(%d, %d, %d) ", pixel2[i*w + j].red, 
      pixel2[i*w + j].green, pixel2[i*w + j].blue);
    }
    printf("\n");
  }


  free(pixels);
  free(pixel2);
  return 0;
}
