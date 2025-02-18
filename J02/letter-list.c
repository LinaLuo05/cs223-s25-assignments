// @author: Lina & Owen

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct letter{
  char l;
  struct letter* next;
};
void insert_first(char c, struct letter** head){
  struct letter* n = malloc(sizeof(struct letter));
  n->l = c;
  n->next = *head;
  *head = n;
}
void printList(struct letter* head){
  struct letter* n = head;
  while (n != NULL){
    printf("%c",n->l);
    n = n->next;
  }
  printf("\n");
}
void clear(struct letter* head){
  struct letter* current = head;
  while (current != NULL) {
    struct letter* next = current->next;
    free(current);
    current = next;
  }
}

void removeL(struct letter* head, char r){
  if (head->l == r) {
    if (head->next) {
      struct letter* next = head->next;
      head->l = next->l;
      head->next = next->next;
      free(next);
    }
  }
  if (head->next){
    if (head->next->l == r) {
      struct letter* temp;
      temp = head->next;
      head->next = head->next->next;
      free(temp);
    }
    removeL(head->next,r);
  }
}


int main()
{
  char str[32];
  printf("Enter a word: ");
  scanf("%s",str);
  char s;
  printf("Enter a character to remove: ");
  scanf("%s", &s);
  struct letter* head = NULL;
  for (int i = strlen(str); i>=0 ; i--){
    insert_first(str[i], &head);
  }
  removeL(head,s);
  printList(head);
  clear(head);
  return 0;
}