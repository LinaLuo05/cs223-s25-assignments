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
void insert_first(char *name, float cost, int quantity, struct snack** head){
  struct snack* n = malloc(sizeof(struct snack));
  strcpy(n->name, name);
  n->cost = cost;
  n->quantity = quantity;
  n->next = *head;
  *head = n;
 
}
/**
 * clear and free all items in the list
 */
void clear(struct snack* head){
  struct snack* current = head;
  while (current != NULL) {
    struct snack* next = current->next;
    free(current);
    current = next;
  }
}
/**
 * print the contents of the list
 */
void printList(struct snack* head){
  struct snack* n = head;
  int i = 0;
  while (n != NULL){
    printf("%d) %s\t cost: $%.2f\t quantity: %d\n", i, n->name, n->cost, n->quantity);
    i++;
    n = n->next;
  }
}

/**
 * sort by name
 */
void sortName(struct snack* head){
  
}


/**
 * sort by cost
 */
void sortCost(struct snack* head, int numSnacks){
  
}


/**
 * sort by quantity
 */
void sortQuantity(struct snack* list){

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

    insert_first(name,cost,quantity,&head);
  }
  sortCost(head,numSnacks);
  printList(head); 
  clear(head);
  return 0;
}
