#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE* fp = fopen("test.bin", "wb");

  const char* message = "a-ok";
  fwrite(message, sizeof(unsigned char), 5, fp);

  unsigned int v = 7;
  fwrite(&v, sizeof(unsigned int), 1, fp);

  fclose(fp);

  unsigned char a = 0x7E;
  unsigned char leftMask = 0xC0;
 unsigned char rightMask = 0x03;
 unsigned char left = (leftMask & a) ;
 unsigned char right = (rightMask & a) ;
 unsigned char leftShift = left >> 4;
 unsigned char rightShift = right << 4;
 unsigned flipped = leftShift | rightShift;

 printf("%x", flipped);

}
