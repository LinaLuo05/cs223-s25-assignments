#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
  pid_t ret;

  printf("A\n");

  for (int i = 0; i < 3; i++)
  {
     ret = fork();
     if (ret == 0) // child
     {
        printf("B%d\n", i);
     }
  }

  printf("Z\n");
  return 0;
}