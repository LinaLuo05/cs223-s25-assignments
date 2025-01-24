/***************************************************
 * mathgame.c
 * @author: Lina Luo
 * @version: Jan 24, 2025
 * Implements a math game
 */

#include <stdio.h>

int main() {
  int round = 0; //variable of how many round does the user want to play
  int correct = 0;//varaible of the correct answer
  int guess = 0; //variable of the user's answer

  printf("Welcome to Math Game!\n");
  printf("How many rounds do you want to play? ");
  scanf("%d", &round);//takes in the number of rounds the user wants to play

  //make sure the round user entered is valid
  while (round < 1) {
    printf("Please enter a number greater than 0.\n");
    printf("How many rounds do you want to play?");
    scanf("%d", &round);
  }

  //generate random questions for intented rounds
    for (int i = 0; i < round; i++) {
      int num1 = rand()%10;
      int num2 = rand()%10;
      int answer = num1 + num2;
      printf("\nWhat is %d + %d ?", num1, num2);
      scanf("%d", &guess);
      //keep track of correct rounds
      if (guess == answer) {
        printf("Correct!");
        correct++;
      } else {
        printf("Incorrect:(");
      }
    }
    printf("You answered %d/%d correctly.", correct, round);
    return 0;
  }
