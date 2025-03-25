#include <stdio.h>
#include <stdlib.h>
//#include "other.h"

void endGame(){
  printf("You win! %s\n", secretMessage());
  exit(0);
}

int main(){
  int secret, guess;
  char buf[8];
  printf("Enter secret number:\n");
  scanf("%s", buf);
  guess = atoi(buf);
  secret=getSecretCode();
  if (guess == secret)
    printf("You got it right!\n");
  else{
    printf("You are so wrong!\n");
    return 1;
  }
  printf("Enter the secret string to win:\n");
  scanf("%s", buf);
  if (!compareSecretString(buf, 8)){
    printf("You lose!\n");
    return 2;
  }
  endGame();
  return 0;
}
