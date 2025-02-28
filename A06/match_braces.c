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
  int line;
  int colomn;
  struct node* next;
};

void push(int line, int colomn, struct node** head){
  struct node* n = malloc(sizeof(struct node));
  n->line = line;
  n->colomn = colomn;
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
    printf("%d) Line %d and Colomn %d\n", i, n->line, n->colomn);
    i++;
    n = n->next;
  }
}

void clear(struct node* head){
  struct node* current = head;
  while (current != NULL) {
    struct node* next = current->next;
    free(current);
    current = next;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE* infile = fopen(filename, "r");
  if (!infile){
    printf("Cannot open file: %s\n", argv[1]);
    return 1;
  }

  struct node* stack = NULL;
  int line = 1;
  int colomn = 1;
  
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

