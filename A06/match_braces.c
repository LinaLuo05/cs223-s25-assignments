/**
 * @author Lina Luo
 * @date  Feb 28, 2025
 * This program takes a C file as a command line argument 
 * and uses a stack to check for matched braces. 
 * If not all braces are matched, it prints the line where a mis-matched brace occurs.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
  char c;
  int line;
  int column;
  struct node* next;
};

void push(int line, int colomn, struct node** head){
  struct node* n = malloc(sizeof(struct node));
  n->c = c;
  n->line = line;
  n->column = column;
  n->next = *head;
  *head = n;
}

struct node pop(struct node* head){
  struct node target = *head;
  head = target->next;
  return target;
}

void printList(struct node* head){
  struct node* n = head;
  int i = 0;
  while (n != NULL){
    printf("%d) Line %d and Colomn %d\n", i, n->line, n->column);
    i++;
    n = n->next;
  }
}
/*
void clear(struct node** head) {
  struct node* current = *head;
  while (current != NULL) {
      struct node* next = current->next;
      free(current);
      current = next;
  }
  *head = NULL;
}
*/

int main(int argc, char** argv)
{
  //Print the usage if the user inputs an incorrect number of command line arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }

  FILE* infile = fopen(filename, "r");
  if (!infile){
    printf("Cannot open file: %s\n", argv[1]);
    return 1;
  }

  struct node* stack = NULL;
  int line = 1;
  int column = 1;
  int ch;
  
  while (fgetc(infile) != NULL){
    char curr = fgetc(infile);
    if (curr == '{'){
      push(line,colomn, stack);
    }
    elif (curr == '}'){
      pop(struct);

    }
    elif (curr = '\n'){
      line ++;
      colomn = 0; 
    }
    else{
      colomn ++;
    }
    

  }






  



  return 0;
}

