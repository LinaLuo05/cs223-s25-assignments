#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int childProcess(int n, int argc, char **argv) {
  int localCount = 0; 
  int i = n;
  int nprocess = atoi(argv[1]);
  char *keyword = argv[2]; 
  int numFiles = argc - 3; 
  char** fileList = &argv[3];
  int subsize = numFiles / nprocess;
  int extra = numFiles % nprocess;

  int start;
  int end;
  start = i*(subsize);
  if (i == nprocess - 1) {
    end = (i + 1) * subsize + extra;
  } else {
    end = (i + 1) * subsize;
  }
  printf("Process [%d] searching for %d files (%d to %d)\n", 
    getpid(), end - start, start, end);
  
  for (int j = start; j < end; j++) {
    FILE *fp = fopen(fileList[j], "r");
    if (!fp){
      fprintf(stderr, "Error: Cannot open file %s\n", fileList[j]);
      return 0;
    }

    char buffer[1000];
    while(fgets(buffer, sizeof(buffer), fp)){
      if (strstr(buffer, keyword)){
        localCount++;
        printf(ANSI_COLOR_MAGENTA "Process [%d] %s" ANSI_COLOR_BLUE ": " ANSI_COLOR_RESET "%s", 
          getpid(), fileList[j], buffer);
      }
    }
    fclose(fp);
  }
  printf("Process [%d] found %d lines containing of keyword: %s\n", getpid(), localCount, keyword);
  return localCount;
} 

int main(int argc, char **argv) {
  if (argc < 4) {
      fprintf(stderr, "usage: %s <NumProcesses> <Keyword> <Files>\n", argv[0]);
      return 1;
  }

  // Read the number of process to create from the command line.
  int nprocess = atoi(argv[1]);
  printf("Searching %d files for keyword: %s\n", argc - 3, argv[2]);

  struct timeval start, end;
  gettimeofday(&start, NULL);
  //creating n processes
  for (int i = 0; i < nprocess; i++) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
      int count = childProcess(i, argc, argv);
      exit(count);
    }
  }
  // Parent collects results after all children are created
  int total = 0;
  int status;
  pid_t child_pid;
  
  // Wait for all children to complete
  for (int i = 0; i < nprocess; i++) {
      child_pid = wait(&status);
      if (WIFEXITED(status)) {
          total += WEXITSTATUS(status);
      }
  }

  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
  printf("Total occurrences: %d\n", total);
  printf("Elapsed time is %.6f\n", elapsed);
  return 0;
}
