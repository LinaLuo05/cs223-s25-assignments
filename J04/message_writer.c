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
    printf("usage: ./message_writer filename\n");
    return 0;
  }

  FILE *fp = fopen(argv[1], "wb");
  if (!fp) {
    printf("Invalid filename. Exiting...\n");
    return 0;
  }

  fprintf(fp, "# This is a comment\n");

  struct meta_data data = {0.15, 2025, 46};
  fwrite(&data, sizeof(struct meta_data), 1, fp);

  char message[47] = "Hello! This is my message! Have a nice day. :)";
  for (int i = 0; i < strlen(message) + 1; i++) {
    fwrite(&message[i], sizeof(char), 1, fp);
  }

  fclose(fp);
  return 0;
}