/***************************************************
 * Author: Lina Luo
 * @date: Jan 31, 2025
 * This program asks the user for a word and creates a bad password from it
 */
#include <stdio.h>
#include <string.h>

int main() {
  char *password = NULL;

  //malloc memory for password
  password = malloc(sizeof(char) * 100);

  //asking for input
  printf("Enter a word:");
  scanf("%s", password);

  //Replace 'e’s with '3’s;Replace 'l’s with '1’s; Replace 'a’s with '@'
  for (int i = 0; i < strlen(password); i++){
    if (password[i] == 'e') {
      password[i] = '3';
    }
    else if (password[i] == 'l') {
      password[i] = '1';
    }
    else if (password[i] == 'a'){
      password[i] == '@';
    }
  };

  //Print the bad password
  printf("Your bad password is: %s\n", password);
  
  //free memory
  free(password);
  
  return 0;
}
