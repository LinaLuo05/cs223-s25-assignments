#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/* signal handler for SIGALRM */
void parent_sigalarm_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Polo\n");
    fflush(stdout);
  }
}

void child_sigalarm_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Marco\n");
    fflush(stdout);
    // Send SIGALRM back to the parent process
    kill(getppid(), SIGALRM);
  }
}

void child_sigterm_handler(int sig) {
  exit(0);
}


int main()
{
  pid_t pid = fork();
  pid_t childPid;
  int input;
  if (pid == 0) {  // Child process
    // Set up the child's SIGALRM handler
    signal(SIGALRM, child_sigalarm_handler);
    signal(SIGTERM, child_sigterm_handler);  // Handle SIGTERM to exit cleanly


    // Wait indefinitely for signals
    while (1) {
      pause();
    }
    exit(0); 
  }
  else{ //parent
    printf("Parent is %d\n", getpid());
    fflush(stdout);
    // Set up the parent's SIGALRM handler
    signal(SIGALRM, parent_sigalarm_handler);
    int input;
    // Read user input
    while (1){
      input = getchar();
      if (input == 'm'){
        kill(pid, SIGALRM);
      }
      else if (input =='q'){
        kill(pid,SIGTERM);
        break;
      }
    }
    // Wait for the child process to terminate to avoid a zombie process
    wait(NULL);
  }
  return 0;
}

