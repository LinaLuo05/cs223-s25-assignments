/*----------------------------------------------
 * Author: Lina Luo
 * Date: March 7, 2025
 * Description:  This program that reads in a 
 * single 64-bit unsigned integer (e.g. unsigned long) 
 * and outputs it as an 8x8 1bpp sprite.
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  
  unsigned long mask = 0x1ul << 63;
  for (int j = 0; j < 8; j++){
    for (int i =0; i < 8; i++){
      if (img & mask){
        printf("@ ");
      }
      else{
        printf("  ");
      }
      mask = mask >> 1;    
    }
    printf("\n");
  }

  return 0;
}
