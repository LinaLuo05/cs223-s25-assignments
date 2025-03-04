#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void print_binary(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (x >> i) & 1);
        // Print a space every 4 bits for better readability
        if (i % 4 == 0)
            printf(" ");
    }
}
int main(int argc, char** argv) {
    if (argc != 4){
        fprintf(stderr, "Usage: %s\n", argv[0]);
    }

    unsigned int num = (unsigned int)strtoul(argv[1], NULL, 0);
    int bit = atoi(argv[2]);
    int flag = atoi(argv[3]);

    printf("Your original number: 0x%x (%u)\n", num, num);

    if (flag == 1) {
        // Set the specified bit using bitwise OR.
        num = num | (1u << bit);
    } else {
        // Clear the specified bit using bitwise AND with the inverted mask.
        num = num & ~(1u << bit);
    }
    printf("Your new number: 0x%x (%u)\n", num, num);



}