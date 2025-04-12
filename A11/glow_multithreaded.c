#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"


struct threads_data{
  long thread_id;
  int start_index;
  int end_index;
  int w;
  int h;
  int threshold;
  int blursize;
  struct ppm_pixel *original;
  struct ppm_pixel *brightImage; 
  struct ppm_pixel *blurredImage;
  struct ppm_pixel *finalImage;
};

void* subImage(void *userdata){
  struct threads_data *data = (struct threads_data *)userdata;
  //bright
  for (int i = data->start_index; i < data->end_index; i ++){
    for (int j = 0; j < data->h; j ++){
      int idx = i * data->w + j;
      int brightness = (data->original[idx].red + data->original[idx].green + data->original[idx].blue) / 3;
      if (brightness >= data->threshold) {
        data->brightImage[idx]= data->original[idx];
      } else {
        data->brightImage[idx].red = 0;
        data->brightImage[idx].green = 0;
        data->brightImage[idx].blue = 0;
      }
    }
  }

  //blur
  for (int i = data->start_index; i < data->end_index; i ++){
    for (int j = 0; j < data->h; j++){
      int sumRed = 0, sumGreen = 0, sumBlue = 0;
      // Loop over the kernel from
      for (int m = -data->blursize/2; m <= data->blursize/2; m++) {
        for (int n = -data->blursize/2; n <= data->blursize/2; n++) {
          int ni = i + m;
          int nj = j + n;
          // Clamp row index
          if (ni < data->start_index) {
            ni = data->start_index;
          } else if (ni >= data->end_index) {
            ni = data->end_index - 1;
          }
          // Clamp column index
          if (nj < 0) {
            nj = 0;
          } else if (nj >= data->h) {  
            nj = data->h - 1;
          }
          int nidx = ni * data->w + nj;
          sumRed   += data->brightImage[nidx].red;
          sumGreen += data->brightImage[nidx].green;
          sumBlue  += data->brightImage[nidx].blue;
        }
      }
    int idx = i * data->w + j;
    data->blurredImage[idx].red   = sumRed / 625;
    data->blurredImage[idx].green = sumGreen / 625;
    data->blurredImage[idx].blue  = sumBlue / 625;
  }
}

  //combine the blue and original
  for (int i = data->start_index; i < data->end_index; i ++) {
    for (int j = 0; j < data->h; j++) {
      int idx = i * data->w + j;
      int red   = data->original[idx].red  + data->blurredImage[idx].red;
      int green = data->original[idx].green + data->blurredImage[idx].green;
      int blue  = data->original[idx].blue  + data->blurredImage[idx].blue;
      data->finalImage[idx].red   = (red > 255) ? 255 : red;
      data->finalImage[idx].green = (green > 255) ? 255 : green;
      data->finalImage[idx].blue  = (blue > 255) ? 255 : blue;
    }
  }
  return NULL;
}


int main(int argc, char* argv[]) 
{
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atof(optarg); break;
      case 'b': blursize = atof(optarg); break;
      case 'f': filename = optarg; break;
      case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); break;
    }
  }

  // todo: your code here
  int w,h;
  struct ppm_pixel *original = read_ppm(filename, &w, &h);
  if (!original) {
    fprintf(stderr, "Failed to open input file\n");
    return 1;
  }
  struct ppm_pixel *brightImage = malloc(w * h * sizeof(struct ppm_pixel));
  struct ppm_pixel *blurredImage = malloc(w * h * sizeof(struct ppm_pixel));
  struct ppm_pixel *finalImage = malloc(w * h * sizeof(struct ppm_pixel));

  pthread_t *threads;
  struct threads_data *data;

  threads = malloc(sizeof(pthread_t)*N);
  data = malloc(sizeof(struct threads_data)*N);

  int subsize = w / N;
  for (int i = 0; i < N; i++) {
    data[i].thread_id = i;
    data[i].start_index = i*(subsize);
    data[i].end_index = (i+1)*(subsize);
    data[i].w = w;
    data[i].h = h;
    data[i].threshold = threshold;
    data[i].blursize = blursize;
    data[i].original = original;
    data[i].brightImage = brightImage;
    data[i].blurredImage = blurredImage;
    data[i].finalImage = finalImage;
    pthread_create(&threads[i], NULL, subImage, &data[i]);
    printf("Thread sub-image slice: rows (%d to %d)\n", data[i].start_index, data[i].end_index);
  }
  
  //wait for threads to join
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  //compute image
  write_ppm("glow.ppm", finalImage, w, h);

  // Free allocated memory
  free(original);
  free(brightImage);
  free(blurredImage);
  free(finalImage);
  free(data);
  free(threads);
  
  return 0;
}
