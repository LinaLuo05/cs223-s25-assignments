#include <stdio.h>

int main() {
    int arr[] = {4, 6, 8, 8, 6, 2, 3, 4, 3};
    int odd_element = 0;

    for (int i = 0; i<9; i++){
        odd_element = odd_element ^ arr[i];
    }

    printf("odd element is: %d\n", odd_element);


}
