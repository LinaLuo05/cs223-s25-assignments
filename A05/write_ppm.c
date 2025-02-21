/*----------------------------------------------
 * Author: Lina Luo
 * Date: feb 20
 * Description: writes to a file test.ppm by calling your function
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE* outfile = fopen(filename, "wb");
    fprintf(outfile,"P6\n#comments\n%d %d 255 ", w, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fwrite(&pixels[i * w + j], sizeof(struct ppm_pixel), 1, outfile);
        }
    }    
    fclose(outfile);

}


void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
