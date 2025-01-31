/***************************************************
 * Author: Lina Luo 
 * @date: Jan 31, 2025
 * This program asks the user for a word and then encodes it using a shift cypher
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char word[100];
  int* shift = malloc(sizeof(int));

  printf("Enter a word:");
  scanf("%s", word);

  printf("Enter a shift:");
  scanf("%d", shift);
  
  for (int i = 0; i < strlen(word); i++) {
    word[i] = word[i] + *shift;
    if (word[i] > 'z') {
      word[i] = word[i] - 26;
    }
    if (word[i] < 'a'){
      word[i] = word[i] + 26;
    }
  }

  printf("Your cypher is %s\n", word);

  free(shift);

  return 0;
}

