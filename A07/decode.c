/*----------------------------------------------
 * Author: Lina Luo
 * Date: March 7, 2025
 * Description: This program reads in a PPM file (raw, or binary, format),
 * and then outputs any message that might be stored in the least significant bits of each color.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
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

  int msg_index = 0;
  int total_pixels = w * h;
  for (int i = 0; i < total_pixels; i++){
    message[msg_index] = (image[i].red & 0x01);
    msg_index++;
    message[msg_index] = (image[i].green & 0x01);
    msg_index++;
    message[msg_index] = (image[i].blue & 0x01);
    msg_index++;
  }
  message[msg_index] = '\0';

  for (int i = 0; i < max_chars; i++){
    unsigned char ch = 0;
    for (int j = 0; j < 8; j++){
      ch = (ch << 1) | message[i * 8 + j];
    }
    if (ch == '\0')
      break;
    printf("%c", ch);
  }
  free(message);
  free(image);
  fclose(fp);
  return 0;
}

