#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int val;
    struct node* next;
};

void insert_first(int val, struct node** head){
    struct node* n = malloc(sizeof(struct node));
    n->val = val;
    n->next = *head;
    *head = n;
}

void insert_last(int val, struct node** head){
    struct node* n = malloc(sizeof(struct node));
    n->val = val;
    n->next = NULL;
    struct node* first = *head;
    while(first->next != NULL){
        first = first ->next;
    }
    first->next = n;
}

void swap(struct node** list){
    struct node* first = *list;
    struct node* first_next = first-> next;
    struct node* last_prev = first;
    struct node* last = last_prev->next;
    if (first->next->next == NULL) {
        struct node* second = first->next;
        second->next = first;
        first->next = NULL;
        *list = second;
        return;
    }
    while(last->next != NULL){
        last_prev = last;
        last = last->next;
    }
    *list = last;
    last ->next = first_next;
    last_prev->next = first;
    first->next = NULL;
}

void printList(struct node* head){
    struct node* n = head;
    int i = 0;
    while (n != NULL){
      printf("%d) %d \n", i, n->val);
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


int main() {
    struct node* list = NULL;
    insert_first(1,&list);
    insert_first(2, &list);
    insert_first(3,&list);
    swap(&list);
    insert_last(4,&list);
    printList(list);
    clear(list);
    


    return 0;
  }
  
  