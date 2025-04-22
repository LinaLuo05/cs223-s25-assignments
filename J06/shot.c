#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int sig) {
  if (sig == SIGINT) {
    printf("Help! I've been shot!");
    fflush(stdout);
    exit(0);
  }
}
int main()
{
  signal(SIGINT, handler);
  while (1) {
  }
  return 0;
}
