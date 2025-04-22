#include <stdio.h>
#include <stdlib.h>


struct data {
    char a;
};

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("usage: %s <NumThreads> <NumTrips>\n", argv[0]);
        return 0;
    }
    char* filename = argv[1];

    FILE* fp = fopen(filename, "rb");
    char c = fgetc(fp);
    while (c != EOF)
    {
        c = c>>1;
        c = c|0b1000000 ;
        printf("%c", c);
        c = fgetc(fp);
    }

    fclose(fp);

    return 0;
}
