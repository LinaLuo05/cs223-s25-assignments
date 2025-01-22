/***************************************************
 * mathgame.c
 * Author: Lina Luo
 * Implements a math game
 */

#include <stdio.h>

int main() {
  printf("Welcome to Math Game!\n");
  int round;
  printf("How many rounds do you want to play? ");
  scanf("%d", &round);//takes in the number of rounds the user wants to play
  while (round < 1) {//if the user enters a number less than 1, the program will ask the user to enter a number greater than 0
    printf("Please enter a number greater than 0.\n");
    printf("How many rounds do you want to play? ");
    scanf("%d", &round);
  }
    int correct = 0;
    for (int i = 0; i < round; i++) {
      int num1 = rand()%10;
      int num2 = rand()%10;
      int answer = num1 + num2;

      int guess = scanf("What is %d + %d ?", num1, num2);
      if (guess == answer) {
        printf("Correct!\n");
        correct++;
      } else {
        printf("Incorrect:(\n");
      }
    }
    printf("You answered %d correctly.\n", correct/round);
    return 0;
  }




