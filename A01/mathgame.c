/***************************************************
 * mathgame.c
 * Author: Lina Luo
 * Implements a math game
 */

#include <stdio.h>

int main() {
  printf("Welcome to Math Game!");
  int round = scanf("How many rounds do you want to play?");
  int correct = 0;
  for (int i = 0; i < round; i++) {
    int num1 = rand();
    int num2 = rand();
    int answer = num1 + num2;
    printf("What is %d + %d?", num1, num2);
    int guess = scanf("Your answer: ");
    if (guess == answer) {
      printf("Correct!");
      correct++;
    } else {
      printf("Incorrect:(");
    }
  }
  printf("You answered %d correctly.", correct/round);
  return 0;
}
