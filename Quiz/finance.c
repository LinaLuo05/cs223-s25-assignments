#include <stdio.h>

int main() {
  unsigned int balance = 0;

  FILE* infile = fopen("finances.txt", "r");
  fscanf(infile, " %u", &balance);
  fclose(infile);

  printf("Your balance: $%u\n", balance);
  printf("What would you like to do? (d = deposit,w = withdraw)\n");
  char choice = fgetc(stdin);
  if (choice != 'd' && choice != 'w') {
    printf("Invalid choice! Quitting....\n");
    return 1;
  }

  int amount = 0;
  printf("Enter an amount: ");
  scanf(" %d", &amount);
  if (amount < 0) {
    printf("Invalid amount! Quitting...\n");
    return 1;
  }

  if (choice == 'd') {
    balance += amount;
  } else if (choice == 'w') {
    if (amount > balance) {
        printf("Error: Insufficient funds!\n");
        return 1;
    }
    balance -= amount;
  }

  FILE* outfile = fopen("finances.txt", "w");
  fprintf(outfile, "%u", balance);
  fclose(outfile);

  return 0;
}