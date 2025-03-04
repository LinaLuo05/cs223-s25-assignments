#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pirntBinary(char* binary){
  char num[100];
  strncpy(num, binary+2, strlen(binary)-2);
  num[strlen(binary)-2] = '\0';
  //printf("%s", num);
  int len = strlen(num);
  int val = 0;
  for (int i = 0; i< len; i ++){
    val += 2^(len-i-1) * num[i];
  }
  printf("%d", val);
}

void printHex(char* hex){

}

int main(int argc, char** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }
  if (argv[1][1] == 'x'){
    printHex(argv[1]);
  }
  if (argv[1][1] == 'b'){
    pirntBinary(argv[1]);
  }

  return 0;
}
