#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data {
  float version;
  unsigned int year;
  unsigned int length;
};

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage: ./message_reader filename\n");
    return 0;
  }
  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    printf("Invalid filename. Exiting...\n");
    return 0;
  }

  char line[256];
  fgets(line, 256, fp); //read comment line
  printf("Comment: %s\n", line);

  struct meta_data *data = (struct meta_data*) malloc(sizeof(struct meta_data));
  fread(data, sizeof(struct meta_data), 1, fp);
  printf("Version: %0.2f\nYear: %u\nLength: %u\n", data->version, data->year, data->length);

  char *chars = (char*) malloc(sizeof(char) * (data->length + 1));
  for (int i = 0; i < data->length + 1; i++) {
    fread(&chars[i], sizeof(char), 1, fp);
  }
  printf("Message: %s\n", chars);

  free(data);
  free(chars);
  fclose(fp);
  return 0;
}