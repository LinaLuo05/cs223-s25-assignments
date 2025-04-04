#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct threads_data{
  long thread_ids;
  int start_index;
  int end_index;
  char **files;
  char* keyword;
  int localCount; 
};

void *findKeyword(void *userdata) {
  struct threads_data *data = (struct threads_data *)userdata;
  for (int i = data->start_index; i < data->end_index; i++) {
    FILE *fp = fopen(data->files[i], "r");
    if (!fp){
      fprintf(stderr, "Error: Cannot open file %s\n", data->files[i]);
      return NULL;
    }

    char buffer[1000];
    while(fgets(buffer, sizeof(buffer), fp)){
      if (strstr(buffer, data->keyword)){
        data->localCount++;
        printf(ANSI_COLOR_MAGENTA "(%ld) %s"ANSI_COLOR_BLUE": "ANSI_COLOR_RESET "%s", 
          data->thread_ids, data->files[i],buffer);
      }
    }
    fclose(fp);
  }
  return NULL; // We don't need our threads to return anything.
}

int main(int argc, char **argv) {
  if (argc < 4) {
      fprintf(stderr, "usage: %s <NumProcesses> <Keyword> <Files>\n", argv[0]);
      return 1;
  }

  // Read the number of threads to create from the command line.
  int nthreads = atoi(argv[1]);
  char *keyword = argv[2]; 
  int numFiles = argc - 3; 
  char **fileList = &argv[3];
  printf("Searching %d files for keyword: %s\n", numFiles, keyword);

  int totalOccurrences = 0;
  struct timeval start, end;

  pthread_t *threads;
  struct threads_data *data;

  threads = malloc(sizeof(pthread_t)*nthreads);
  data = malloc(sizeof(struct threads_data)*nthreads);
  
  gettimeofday(&start, NULL);
  int subsize = numFiles / nthreads;
  int extra = numFiles % nthreads;

  // Assign each thread an ID and create all the threads.
  for (int i = 0; i < nthreads; i++) {
    data[i].thread_ids = i;
    data[i].start_index = i*(subsize);
    if(i == nthreads-1){
      data[i].end_index = (i+1)*(subsize) + extra;
    }
    else{
      data[i].end_index = (i+1)*(subsize);
    }
    data[i].files = fileList;
    data[i].keyword = keyword;
    data[i].localCount = 0;
    pthread_create(&threads[i], NULL, findKeyword, &data[i]);
    printf("Thread %ld searching for %d files (%d to %d)\n", data[i].thread_ids, 
      data[i].end_index - data[i].start_index, data[i].start_index, data[i].end_index);
  }

  /* Join all the threads. Main will pause in this loop until all threads
   * have returned from the thread function. */
  for (int i = 0; i < nthreads; i++) {
      pthread_join(threads[i], NULL);
      totalOccurrences += data[i].localCount;  
  }
  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
  printf("Elapsed time is %.6f\n", elapsed);
  for (int i = 0; i < nthreads; i++){
  printf("Thread %ld found %d lines containing of keyword: %s\n", data[i].thread_ids, data[i].localCount, data[i].keyword);
  }
  printf("Total occurrences: %d\n", totalOccurrences);
  

  free(threads);
  free(data);
  return 0;
}
