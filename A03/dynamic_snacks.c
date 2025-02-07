/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 7, 2025
 * Description: a program that allows users to add snacks to the snackbar, and show the list of snacks. 
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//define a structure to store information about a snack.
struct snack {
    char name[100];
    float cost;
    int quantity;
  };

int main() {
  //ask for the number of snacks the user wants to add
  int numSnacks;
  printf("Enter a number of snacks:");
  scanf("%d", &numSnacks);

  //create an array of struct snack
  struct snack* snackArray = malloc(numSnacks * sizeof(struct snack));
  
  //loop to read the details for each snack from the user 
  for (int i = 0; i < numSnacks; i++){
    printf("Enter a name:");
    scanf("%s", snackArray[i].name);

    printf("Enter a cost:");
    scanf("%f", &snackArray[i].cost);

    printf("Enter a quantity:");
    scanf("%d", &snackArray[i].quantity);
  }

  printf("Welcome to Dynamic Donna's Snack Bar.\n");
  for (int i = 0; i < numSnacks; i++) {
    printf("%d) %s\t cost: $%.2f\t quantity: %d\n", i, snackArray[i].name, snackArray[i].cost, snackArray[i].quantity);
  }
  

  free(snackArray);
  return 0;
}
