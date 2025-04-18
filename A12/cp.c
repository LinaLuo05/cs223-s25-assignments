#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

//Global
int num_items=0, in=0, out=0, buff[N];
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
}

int main() {
  
  void* producer_threads(){
    int item;
    while(1) {
      item = produce_item();
      sleep(1);
      pthread_mutex_lock(&mux);
      while(num_items >= N){
        pthread_cond_wait(&full, &mux);
      }
      buff[in] = item;
      in = (in+1)%N;
      num_items++;
      pthread_cond_signal(&empty);
      pthread_mutex_unlock(&mux);
    }
    return NULL;
  }

  void* consumer_threads(){
    int item;
    while(1) {
      pthread_mutex_lock(&mux);
      while(num_items == 0){
        pthread_cond_wait(&empty, &mux);
      }
      item = buff[out];
      out = (out+1)%N;
      num_items--;
      pthread_cond_signal(&empty);
      pthread_mutex_unlock(&mux);
      consume_item(item);
    }
    return NULL;
  }

  pthread_t prod_thread, cons_thread;
  pthread_create(&prod_thread, NULL, producer_threads, NULL);
  pthread_create(&cons_thread, NULL, consumer_threads, NULL);
  
  pthread_join(prod_thread, NULL);
  pthread_join(cons_thread, NULL);

  pthread_mutex_destroy(&mux);
  pthread_cond_destroy(&full);
  pthread_cond_destroy(&empty);
  return 0;
}

