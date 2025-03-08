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

unsigned char* message_to_bits(char *message, int *num_bits) {
  int len = strlen(message) + 1; // Include the null terminator
  *num_bits = len * 8; // Each character is 8 bits
  unsigned char *bits = malloc(*num_bits);
  
  int bit_index = 0;
  for (int i = 0; i < len; i++) {
    unsigned char ch = message[i];
    //Convert each character to binary
    for (int b = 0; b < 8; b++) {
      if (ch & (1 << (7 - b))) {
        bits[bit_index++] = 1;
      } 
      else {
        bits[bit_index++] = 0;
     }
    }
  }
    return bits;
}


void embed_message(struct ppm_pixel *image, int total_pixels, unsigned char *bits, int num_bits) {
  int bit_count = 0;
  // Loop over each pixel.
  for (int i = 0; i < total_pixels && bit_count < num_bits; i++) {
    // For each pixel, update red, green, blue channels in order.
    if (bit_count < num_bits) {
      image[i].red = (image[i].red & 0xFE) | bits[bit_count];
      bit_count++;
    }
    if (bit_count < num_bits) {
      image[i].green = (image[i].green & 0xFE) | bits[bit_count];
      bit_count++;
    }
    if (bit_count < num_bits) {
      image[i].blue = (image[i].blue & 0xFE) | bits[bit_count];
      bit_count++;
    }
  }
}

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
  int max_chars = total_channels / 8 -1;
  printf("Max number of characters in the image: %d\n", max_chars);
  
  char *message = malloc(sizeof(char)* max_chars);
  printf("Enter a phrase:");
  scanf("%s", message);

  //Convert message to unsigned char*
  int num_bits;
  unsigned char* bits = message_to_bits(message,&num_bits);  
  // printf("Bit array:\n");
  // for (int i = 0; i < num_bits; i++) {
  //     printf("%d", bit_array[i]);
  //     // Print a space after every 8 bits to separate each character
  //     if ((i + 1) % 8 == 0) {
  //         printf(" ");
  //     }
  // }
  // printf("\n");

  //Embed the message to image
  embed_message(image,total_channels, bits, num_bits);

  //Give the outfile a new name
  char outfileName[256];
  int i;
  for (i = 0; i < strlen(filename) - 4; i++) {
      outfileName[i] = filename[i];
  }
  outfileName[i] = '\0';
  strcat(outfileName, "-encoded.ppm");

  write_ppm(outfileName,image,w,h);
  printf("Writing file %s\n", outfileName);


  free(image);
  free(bits);
  free(message);
  fclose(fp);

  return 0;
}

