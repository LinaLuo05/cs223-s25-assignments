#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  // todo: your code here
  int w,h;
  struct ppm_pixel *original = read_ppm("earth-small.ppm", &w, &h);
  if (!original) {
    fprintf(stderr, "Failed to open input file\n");
    return 1;
  }
  struct ppm_pixel *brightImage = malloc(w * h * sizeof(struct ppm_pixel));
  struct ppm_pixel *blurredImage = malloc(w * h * sizeof(struct ppm_pixel));
  struct ppm_pixel *finalImage = malloc(w * h * sizeof(struct ppm_pixel));


  //mark the bright area
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int idx = i * w + j;
      int brightness = (original[idx].red + original[idx].green + original[idx].blue) / 3;
      if (brightness >= 200) {
        brightImage[idx] = original[idx];
      } else {
        brightImage[idx].red = 0;
        brightImage[idx].green = 0;
        brightImage[idx].blue = 0;
      }

    }
  }

  //blur
  for (int i = 0 ; i < h ; i ++){
    for (int j  = 0; j < w; j++){
     
      int sumRed = 0, sumGreen = 0, sumBlue = 0;
      //go through the neighbor
      for (int m = i-12; m < i+12; m++){
        for (int n = j-12; n < j+12; n++){ 
          int clamped_m = m;
          int clamped_n = n;
          if (clamped_m < 0) clamped_m = 0;
          else if (clamped_m >= h) clamped_m = h - 1;
          if (clamped_n < 0) clamped_n = 0;
          else if (clamped_n >= w) clamped_n = w - 1;
          
          int nidx = clamped_m * w + clamped_n;
          sumRed   += brightImage[nidx].red;
          sumGreen += brightImage[nidx].green;
          sumBlue  += brightImage[nidx].blue;
        }
      }
      int idx = i * w + j;
      blurredImage[idx].red = sumRed / 25;
      blurredImage[idx].green = sumGreen / 25;
      blurredImage[idx].blue  = sumBlue / 25;
    }
  }

  // compute image
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int idx = i * w + j;
      int red   = original[idx].red   + blurredImage[idx].red;
      int green = original[idx].green + blurredImage[idx].green;
      int blue  = original[idx].blue  + blurredImage[idx].blue;
      finalImage[idx].red = red;
      finalImage[idx].green = green;
      finalImage[idx].blue = blue;
    }
  }

  //write ppm
  write_ppm("glow.ppm", finalImage, w, h);

  // Free allocated memory
  free(original);
  free(brightImage);
  free(blurredImage);
  free(finalImage);
  
  return 0;
}
