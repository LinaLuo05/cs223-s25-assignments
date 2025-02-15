/*----------------------------------------------
 * Author: Lina Luo
 * Date: Feb 14, 2025
 * Description: this program allows users to add snacks to the snackbar and displays them in alphabetical order.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct snack {
  char name[100];
  float cost;
  int quantity;
  struct snack* next;
};
/**
 * create a new snack struct and insert it at the beginning of the list
 */
void insert_first(char *name, float cost, int quantity, struct snack* head){
  struct snack* n = malloc(sizeof(struct snack));
  strcpy(n->name, name);
  n->cost = cost;
  n->quantity = quantity;
  n->next = head;
  head = n;
}
/**
 * clear and free all items in the list
 */
void clear(struct snack* head){
  struct snack* next = NULL;
  while(next != NULL){
    next = head->next;
    free(head);
    clear(next);
  }
}
/**
 * print the contents of the list
 */
void printList(struct snack* head){
  for (struct snack* n = head; n!= NULL; n = n->next){
    printf("%d) %s\t cost: $%.2f\t quantity: %d\n", i, head->name, head->cost, head->quantity);
    i++;
    printList(next);
  }
}

int main() {
  //ask for the number of snacks the user wants to add
  int numSnacks;
  printf("Enter a number of snacks:");
  scanf("%d", &numSnacks);

  //create head of the linked list 
  struct snack* head = NULL;

  //loop to read the details for each snack from the user 
  for (int i = 0; i < numSnacks; i++){
    char name[100];
    float cost = 0.0;
    int quantity = -1;
    printf("Enter a name:");
    scanf("%s", name);

    printf("Enter a cost:");
    scanf("%f", &cost);

    printf("Enter a quantity:");
    scanf("%d", &quantity);

    insert_first(name,cost,quantity,head);
  }
  printList(head); 

  return 0;
}
