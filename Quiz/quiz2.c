#include <stdio.h>
#include <string.h>

/** 
 * name has no '\0' , strlen(name) doesn't work-->jump or move depends on uninitialised value(s)
int main() {
  char name[16];
  //printf("%s", name);
  memset(name,'z',sizeof(char)*15); //no '\0'
  name[15] = '\0'; 
  for (int i = 0; i < strlen(name)-1; i++) { 
    name[i] = i+'a';
  }
  name[15] = '\0';
  printf("Name is %s\n", name);
  return 0;
}
*/

/** #include <stdio.h>
#include <stdlib.h>

int main() {
  FILE* fp = fopen("test.txt", "r");
  if (!fp) {
    printf("Cannot open file\n");
    exit(1);
  }

  int ch = 0;
  while (ch != EOF) {
    ch = fgetc(fp);
  }
  fclose(fp); //fclose frees all resources.
  //free(fp);
  fp = NULL;
}
  */
/*
 * Copyright (c) 2020, Dive into Systems, LLC (https://diveintosystems.org/)
 * Program with a segfault
 */


 // segmentation fault: no memory allocated to a pointer; 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initfunc(int *array, int len) {
    int i;
    for (i=1; i < len; i++) {
        array[i] = i;
    }
    return 0;
}

int func(int *array1, int len, int max) {
    int i;
    max = array1[0];
    for (i=1; i < len; i++) {
        if (max < array1[i]) {
            max = array1[i];
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    int *arr = malloc(sizeof(int) * 100);
    memset(arr, 0, sizeof(int)*100);
    int max = 6;
   

    if (initfunc(arr, 100) != 0 ) {
        printf("init error\n");
        exit(1);
    }

    if ( func(arr, 100, max) != 0 ) {
        printf("func error\n");
        exit(1);
    }
    printf("max value in the array is %d\n", max);
    free(arr);
    exit(0);
}
