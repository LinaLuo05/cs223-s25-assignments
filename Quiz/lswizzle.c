#include <stdio.h>
void print_binary(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (x >> i) & 1);
        // Print a space every 4 bits for better readability
        if (i % 4 == 0)
            printf(" ");
    }
}

int first_bit(unsigned int x){
    for (int i = 31; i >= 0; i--) {
        if (x & (1u << i)) {
            // Found the first 1 at position i
            printf("%d\n", i);
            return i;
        }
    }
}

int main() {
  unsigned int input;
  printf("input the unsigned int:");

  scanf("%dx", &input);
  print_binary(input);
  printf("\n");
  // Get the most significant bit (MSB)
  int n = first_bit(input);
  
  unsigned int msb = input >> (n);
  print_binary(msb);
  printf("\n");

  //(sizeof(unsigned int) * 8 gives how many bits is the unsigned int
  // -1 make the shift to preserve only the most significant bit
  
  // Shift left and wrap the MSB into the LSB position
  unsigned int output = (input << (32-n)) | msb;
  // | operation writes
  // & operation is the mask
  printf("output:\n");
  print_binary(output);


  return 0;
}
