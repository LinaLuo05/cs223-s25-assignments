/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 20, 2025
 * Description: read PPM files stored in binary format. 
 * This function takes a filename as input and return a 2D 
 * array of struct pixel.
 * // filename is the image PPM to open and read
// width should point to a variable for storing the width
// height should point to a variable for storing the height
 ---------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "read_ppm.h"
 
 // Choose *one* to implement (do not remove the other one!)
 struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
   FILE* infile = fopen(filename, "rb");
   if (!infile){
     printf("Error. Invalid file name.\n");
     return NULL;
   }
 
   char buffer[1000];
   // Read header
   fgets(buffer, sizeof(buffer), infile); // Read "P6"
   // Read comment line
   fgets(buffer, sizeof(buffer), infile); 
 
   // Read width and hight
   fscanf(infile, "%d %d", w,h);
 
   // Read the maxval
   int maxval;
   fscanf(infile, "%d", &maxval);
 
   // Read a whitespace
   fgetc(infile);
 
   // Malloc space for the list
   struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));
 
    
   for (int i = 0; i < (*h); i++) {
     for (int j = 0; j < (*w); j++) {
       fread(&image[i * (*w) + j].red, 1, 1, infile);
       fread(&image[i * (*w) + j].green, 1, 1, infile);
       fread(&image[i * (*w) + j].blue, 1, 1, infile);
     }
   }
 
   fclose(infile);
   return image;
 }
 
 
 struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
   return NULL;
 }
 
 
 