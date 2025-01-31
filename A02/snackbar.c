/***************************************************
 * Author: Lina Luo
 * @date: Jan 31, 2025
 * This program maintains a list of snacks available for purchase
 */
#include <stdio.h>
#include <string.h>

typedef struct snack {
  char name[100];
  float cost;
  int quantity;
}snack;


int main() {
  float money;

  printf("Welcome to Steven Struct's Snack Bar.\n");

  //ask the user how much money they have
  printf("How much money do you have?");
  scanf("%f", money);

  //define the snacks
  snack CocoPuffs, ManchegoCheese, MagicBeans;
  strcpy(CocoPuffs.name, "Coco Puffs");
  CocoPuffs.cost = 1.50;
  CocoPuffs.quantity = 4;

  strcpy(ManchegoCheese.name, "Manchego Cheese");
  ManchegoCheese.cost = 15.50;
  ManchegoCheese.quantity = 6;

  strcpy(MagicBeans.name, "Magic Beans");
  MagicBeans.cost = 0.50;
  MagicBeans.quantity = 0;

  //store the snacks in an array
  snack snackArray[3];
  snackArray[0] = CocoPuffs;
  snackArray[1] = ManchegoCheese;
  snackArray[2] = MagicBeans;
  
  //print the snacks
  for (int i = 0; i < 3; i++) {
    printf("%d ) %s\t cost: $%.2f\t quantity: %d\n", i, snackArray[i].name, snackArray[i].cost, snackArray[i].quantity);
  }

  //ask the user which snack they want to buy
  int choice;
  printf("What snack would you like to buy? [0,1,2]");
  scanf("%d", &choice);

  //reply
  if (choice < 0 || choice > 2) {
    printf("Invalid choice\n");
  } else if (snackArray[choice].quantity == 0) {
    printf("Sorry, we are out of %s\n", snackArray[choice].name);
  } else if (money < snackArray[choice].cost) {
    printf("You can't afford it!\n");
  } else {
    printf("You bought %s\n", snackArray[choice].name);
    money -= snackArray[choice].cost;
    snackArray[choice].quantity--;
    printf("You have $%f left\n", money);
  }

  return 0;
}