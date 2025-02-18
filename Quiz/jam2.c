#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Write a program that reads in a text file and writes it to a new file with each word reversed.
 */

void txt_reversed(char* name){
    FILE *infile; 
    FILE *outfile;
    infile= fopen(name, "r");
    if (infile== NULL) {
        printf("Error: unable to open file %s\n", "input.txt");
        exit(1);
    }

    outfile= fopen("output.txt", "w");
    if (outfile== NULL) {
        printf("Error: unable to open outfile\n");
        exit(1);
    }
    char buffer[1024];
    //reading the file line by line
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
    //fgets requires three arguments: 
    // a buffer to store the string, the size of that buffer, and the file pointer.
        char *word= strtok(buffer, " ,.!");
        //stores the word
        while (word != NULL){
            int len = strlen(word);
            for (int i = 0; i<len/2; i++){
                char temp = word[i];
                word[i] = word[len-1-i];
                word[len-1-i] = temp;
            }
            fprintf(outfile, "%s \t", word);
            word = strtok(NULL, " ,.!");
            //By passing NULL as the first argument in subsequent calls, 
            //you tell strtok to continue tokenizing the same string from where it left off:
        } 
    }
    fclose(infile);
    fclose(outfile);
}

int main(void) {
    char name[100];
    printf("Please enter input file name: ");
    scanf("%s", name);
    txt_reversed(name);
    return 0;
}


