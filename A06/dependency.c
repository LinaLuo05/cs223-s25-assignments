#include <stdio.h>
#include <string.h>
#include "tree.h"

void printDependency(char* filename){
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Could not open file: %s\n", filename);
    return;
  }

  char line[1024];
  while (fgets(line, sizeof(line), fp)) {
    char *start = strstr(line, "#include");
    if (start != NULL) {
      start += strlen("#include");
      // Skip any whitespace.
      while (*start == ' ' || *start == '\t') {
        start++;
      }
      // Check for the opening delimiter: either a double quote or '<'
      if (*start == '"' || *start == '<') {
        char delim = *start;  // Save the opening delimiter.
        start++;              // Move past the opening delimiter.
        // Find the corresponding closing delimiter.
        char *end;
        if (delim == '"') {
            end = strchr(start, '"');
        } else {
            end = strchr(start, '>');
        }

        if (end != NULL) {
          int len = end - start;
          char dep[100];  
          strncpy(dep, start, len);
          dep[len] = '\0';
          printf("  %s\n", dep);
        }
      }
    }
  }
  fclose(fp);
}


int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }
  struct tree_node* root = NULL;
  int processedFile = 0;

  // insert each valid file into the tree
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp) {
      fclose(fp);
      root = insert( argv[i],root);
      processedFile++;
    }
  }
  printf("Processing %d files...\n", processedFile);

  //Taking commands from terminal
  char command[100];
  while (1) {
    printf("$ ");
    if (!fgets(command, sizeof(command), stdin))
      break;
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "quit") == 0) {
      break;
    } 
    else if (strcmp(command, "list") == 0) {
      printSorted(root);
    } 
    else {
      struct tree_node *node = find(command, root);
      if (node == NULL) {
        printf("%s not found\n", command);
      } 
      else {
        printf("%s has the following dependencies\n", command);
        printDependency(command);
      }
    }
  }
  clear(root);


  return 0;
}
