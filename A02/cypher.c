/***************************************************
 * Author: Lina Luo 
 * @date: Jan 31, 2025
 * This program asks the user for a word and then encodes it using a shift cypher
 */
#include <stdio.h>
#include <string.h>

int main() {
  char* word;
  int* shift;

  printf("Enter a word:");
  scanf("%s", &word);

  printf("Enter a shift:");
  scanf("%d", &shift);

  for (int i = 0; i < strlen(word); i++) {
    word[i] = word[i] + shift;
  }

  printf("Your cypher is %s\n", word);

  return 0;
}
