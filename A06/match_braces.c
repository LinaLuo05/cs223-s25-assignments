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

void push(char c, int line, int column, struct node** head){
  struct node* n = malloc(sizeof(struct node));
  n->c = c;
  n->line = line;
  n->column = column;
  n->next = *head;
  *head = n;
}

struct node* pop(struct node** head) {
  if (*head == NULL)
      return NULL;
  struct node* top = *head;
  *head = top->next;
  return top;
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
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE* infile = fopen(argv[1], "r");
  if (!infile){
    printf("Cannot open file: %s\n", argv[1]);
    return 1;
  }

  struct node* stack = NULL;
  int line = 1;
  int column = 1;
  int ch;
  
  while ((ch = fgetc(infile)) != EOF) {
    char curr = (char) ch;
    if (curr == '{') {
      push(curr, line, column, &stack);
      column++;
    } else if (curr == '}') {
      struct node* n = pop(&stack);
      if (n == NULL) {
        fprintf(stderr, "Unmatched closing brace at line %d, column %d\n", line, column);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", n->line, n->column, line, column);
        free(n);
      }
      column++;
    } else if (curr == '\n') {
      line++;
      column = 1;
    } else {
      column++;
    }
  }
  while(stack != NULL){
    fprintf(stderr, "Unmatched closing brace at line %d, column %d\n", stack->line, stack->column);
    struct node* n = pop(&stack);
    free(n);
  }
  fclose(infile);

  return 0;
}

