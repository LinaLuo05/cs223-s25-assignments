/*----------------------------------------------
 * Author: Lina Luo
 * Date: feb 7, 2025
 * Description: asks the user for a string s and an integer n and then creates a new string that repeats s n times.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char* word = malloc(33);
  //get the word
  printf("Enter a word:");
  scanf("%s", word);

  //get the count
  int count;
  printf("Enter a count:");
  scanf("%d", &count);

  
  char* newWord = malloc(33*10000);
  //copy the word to newWord count times
  for (int i = 0; i < count; i++){ 
    for (int j = 0; j < strlen(word); j++){ 
      newWord[i*strlen(word) + j] = word[j];
    }
  }
  newWord[count*strlen(word)] = '\0';
  printf("Your word is %s\n", newWord);

  free(word);
  free(newWord);

  return 0;
}
