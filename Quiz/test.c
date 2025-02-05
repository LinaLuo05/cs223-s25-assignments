#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isPalindrome(char* str) {
  int size = strlen(str);
  char newStr[size-2];
  if(size <=1){
    return 1;
  }
  else{
    char a = str[0];
    char b = str[size-1];
    if (a !=b){
      return 0;
    }
    else{
      for (int i = 1; i<size-1; i++){
        newStr[i-1] = str[i];
      }
      newStr[size-2] = '\0';
      strcpy(str,newStr);
      return isPalindrome(str);
    }
  }
}


int main() {
  char* str = (char*)malloc(100);
  printf("input:\n");
  scanf("%s",str);
  printf("%d",isPalindrome(str));
  return 0;
  free(str);
}