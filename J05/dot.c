#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

// your code here
struct threads_data{
  long thread_ids;
  int start_index;
  int end_index;
  int v[100000];
  int u[100000];
  int LocalDotProduct; 
};

//function dotProduct
void *dotProduct(void *userdata) {
  struct threads_data *data = (struct threads_data *)userdata;
  for (int i = data->start_index; i < data->end_index; i++){
    data->LocalDotProduct += data->v[i]*data->u[i];
  }
  return NULL;
}


int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  int thread_dotproduct = 0;
  printf("Test with 4 threads\n");
  pthread_t *threads;
  struct threads_data *data;

  int nthreads = 4;
  threads = malloc(sizeof(pthread_t)*nthreads);
  data = malloc(sizeof(struct threads_data)*nthreads);
  int subsize = SIZE / nthreads;

  // Assign each thread an ID and create all the threads.
  for (int i = 0; i < nthreads; i++) {
    data[i].thread_ids = i;
    data[i].start_index = i*(subsize);
    data[i].end_index = (i+1)*(subsize);
    for (int j = 0; j < SIZE; j++) {
      data[i].v[j] = v[j];
      data[i].u[j] = u[j];
    }
    data[i].LocalDotProduct = 0;
    pthread_create(&threads[i], NULL, dotProduct, &data[i]);
  }

  for (int i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
    thread_dotproduct += data[i].LocalDotProduct;  
  }

  printf("Answer with threads: %d\n", thread_dotproduct);
  free(threads);
  free(data);

  return 0;
}
