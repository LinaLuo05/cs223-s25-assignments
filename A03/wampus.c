/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 7, 2025
 * Description: a program that randomly places a Wampus within a NxM grid.
 ---------------------------------------------*/
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));   
  
  //get the size of grid
  int row;
  printf("Number of rows:");
  scanf("%d", &row);

  int column;
  printf("Number of columns:");
  scanf("%d",&column);

  //create a 2D array
  int* two_d_array = malloc(sizeof(int)*(row*column));

  //randomly place W
  int rowW = rand()%(row);
  int colW = rand()%(column);
  printf("rowW: %d colW%d\n", rowW, colW);
  two_d_array[rowW*row + colW] = 'W';

  //fill the rest of grid with the distance
  for (int i = 0; i < row; i++){
    for (int j = 0; j < column; j++){
      two_d_array[i*row+j] = abs(i - rowW) + abs(j - colW);
    }
  }
  
  //print out the grid
  for (int i = 0; i < row; i++){
    for (int j = 0; j < column; j++){
      if (two_d_array[i*row+j] != 0){
        printf("%d \t", two_d_array[i*row+j]);
      }
      else{
        printf("W\t");
      }
    }
    printf("\n");
  }

  free(two_d_array);
  return 0;
}