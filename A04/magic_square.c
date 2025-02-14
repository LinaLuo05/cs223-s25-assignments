/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 14,2025
 * Description: This program tests whether a given matrix is a magic square.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int row;
  int colomn;

  scanf("%d", &row);
  scanf("%d", &colomn);

  int *two_d_array = malloc(sizeof(int)*(row*colomn));
  for(int i = 0; i < row; i++){
    for(int j = 0; j < colomn; j++){
      scanf("%d",&two_d_array[i*colomn+j]);
    }
  }
  int *constantArray = malloc(sizeof(int)*(colomn+row+1));
  int constant = 0;
  int diagonal = 0;
  int index = 0;//keep track of the index of where to write in constantArray

  //stores the sum of diagonal entries into the constantArray;
  for (int i = 0; i<row; i++){
    for(int j = 0; j <colomn; j++){
      if (i == j){
        diagonal += two_d_array[i*row+j];
      }
    }
  }
  constantArray[index] = diagonal;
  index++;

  //stores the sums of rows into the constantArrary
  for (int i = 0; i<row; i++){
    for(int j = 0; j <colomn; j++){
      constant += two_d_array[i*row+j];
    }
    constantArray[index] = constant;
    index++;
    //printf("%d\t", constant);
    constant = 0;
  }

  //stores the sums of columns into the constantArrary
  for (int i = 0; i<colomn; i++){
    for(int j = 0; j <row; j++){
      constant += two_d_array[j*row +i];
    }
    //printf("%d\t", constant);
    constantArray[index] = constant;
    index++;
    constant = 0;
  }
  //checking whether all the sums are the same
  int first = constantArray[0];
  for (int i = 1; i < index; i ++){
    if (first != constantArray[i]){
      printf("M is NOT a magic square!\n");
      return 1;
    }
  }
  printf("M is a magic square (magic constant = %d)\n", first);
  
  free(two_d_array);
  free(constantArray);
  return 0;
}
