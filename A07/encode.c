/*----------------------------------------------
 * Author: Lina Luo
 * Date: March 7
 * Description: this program reads in a PPM file 
 * (raw, or binary, format) and asks the user for 
 * a message to embed within it.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  FILE* fp = fopen(argv[1], "r");
  if (!fp){
    printf("Cannot open file: %s\n", argv[1]);
    return 1;
  }
  char* filename = argv[1];
  int w;
  int h; 
  struct ppm_pixel* image = read_ppm(filename, &w, &h);
  
  printf("Reading %s with width %d and height %d\n", filename, w, h);
  int total_channels = 3 * w * h;
  int max_chars = total_channels / 8;
  printf("Max number of characters in the image: %d\n", max_chars);
  
  unsigned char *message = malloc(total_channels + 1);
  printf("Enter a phrase:");
  scanf("%s", message);


  int bit_index = 0;
  for (int i = 0; message[i] != '\0'; i++) {
    unsigned char ch = message[i];
    for (int b = 0; b < 8; b++) {
      int bit = (ch << b) & 1; //
      image[bit_index].red = (image[bit_index].red & 0xFE) | bit;
      bit_index++;
      image[bit_index].green = (image[bit_index].green & 0xFE) | bit;
      bit_index++;
      image[bit_index].blue = (image[bit_index].blue & 0xFE) | bit;
      bit_index++;
    }
  }
    // Embed the null terminator (0).
    for (int b = 0; b <8; b++) {
        image[bit_index].red = (image[bit_index].red & 0xFE);
        bit_index++;
    }


  

  return 0;
}

