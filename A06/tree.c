#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root)
{
  if (root == NULL)
    return NULL;
  
  int cmp = strcmp(root->data.name, name);
  if (cmp == 0){
    return root;
  }
  else if (cmp > 0){
    return find(name,root->left);
  }
  else if (cmp < 0){
    return find(name,root->right);
  }
  return NULL;
}

struct tree_node* insert(const char* name, struct tree_node* root)
{
  if (root == NULL){
    struct tree_node* new_node = malloc(sizeof(struct tree_node));
    strncpy(new_node->data.name, name, sizeof(new_node->data.name) - 1);
    new_node->data.name[sizeof(new_node->data.name) - 1] = '\0';
    new_node->left = new_node->right = NULL;
    return new_node;
  }
  else{
    int cmp = strcmp(name, root->data.name);
    if (cmp < 0)
        root->left = insert(name, root->left);
    else if (cmp > 0)
        root->right = insert(name, root->right);
  }
  return root;
}

void clear(struct tree_node* root)
{
  if (root == NULL){
    return;
  }
  clear(root->left);
  clear(root->right);
  free(root);
}

void printright(struct tree_node* right, int indent);

void printleft(struct tree_node* left, int indent){
  if(left == NULL){
    return;
  }
  for (int i =0; i< indent; i++){
    printf(" ");
  }
  printf("l:%s\n", left->data.name);
  printleft(left->left, indent+1);
  printright(left->right, indent+1);
}

void printright(struct tree_node* right, int indent){
  if (right == NULL){
    return;
  }
  for (int i =0; i< indent; i++){
    printf(" ");
  }
  printf("r:%s\n", right->data.name);
  printleft(right->left, indent+1);
  printright(right->right, indent+1);
}

void print(struct tree_node* root)
{
  int indent = 1;
  printf("%s\n", root->data.name);
  printleft(root->left, 1);
  printright(root->right, 1);
}

void printSorted(struct tree_node* root)
{
  if (root == NULL) return;
  printSorted(root->left);
  printf("%s\n", root->data.name);
  printSorted(root->right);
}

