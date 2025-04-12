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
  for (int i = 0; i < h; i++){
    for (int j = 0; j < w; j++){
      int sumRed = 0, sumGreen = 0, sumBlue = 0;
      // Loop over the kernel from -12 to 12 (25 values)
      for (int m = -12; m <= 12; m++) {
        for (int n = -12; n <= 12; n++) {
          int ni = i + m;
          int nj = j + n;
          // Clamp row index
          if (ni < 0) {
            ni = 0;
          } else if (ni >= h) {
            ni = h - 1;
          }
          // Clamp column index
          if (nj < 0) {
            nj = 0;
          } else if (nj >= w) {
            nj = w - 1;
          }
          int nidx = ni * w + nj;
          sumRed   += brightImage[nidx].red;
          sumGreen += brightImage[nidx].green;
          sumBlue  += brightImage[nidx].blue;
        }
      }
    int idx = i * w + j;
    // Divide by the total number of pixels in the kernel: 25 x 25 = 625
    blurredImage[idx].red   = sumRed / 625;
    blurredImage[idx].green = sumGreen / 625;
    blurredImage[idx].blue  = sumBlue / 625;
  }
}

  // compute image
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int idx = i * w + j;
      int red   = original[idx].red   + blurredImage[idx].red;
      int green = original[idx].green + blurredImage[idx].green;
      int blue  = original[idx].blue  + blurredImage[idx].blue;
      finalImage[idx].red   = (red > 255) ? 255 : red;
      finalImage[idx].green = (green > 255) ? 255 : green;
      finalImage[idx].blue  = (blue > 255) ? 255 : blue;
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
