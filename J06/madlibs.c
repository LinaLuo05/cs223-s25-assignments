#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 32

struct adj{
    char adj[MAXSIZE];
};

int main()
{
    int boolean;
    int num;
    char* buff = malloc(sizeof(char)*32);
    printf("Boolean:");
    scanf("%d", &boolean);
    printf("Number:");
    scanf("%d", &num);
    char** adjective = malloc(sizeof(char*)* num);
    char* strBoolean = malloc(MAXSIZE);
    if (boolean){
        strncpy(strBoolean, "true", MAXSIZE);
    }
    else{
        strncpy(strBoolean, "false", MAXSIZE);
    }

    for (int i = 0;i < num; i++){
        printf("Adjective: ");
        scanf("%s", buff);
        adjective[i] =  malloc(MAXSIZE);
        strcpy(adjective[i],buff);
        //printf("%s", adjective[i]);
    }
    //char* strAdj = malloc(sizeof(buff)*(num+1));


    
    printf("You are the most ");
    for (int i = num-1; i>0; i--){
        printf("%s, ", adjective[i]);
        free(adjective[i]);
    }
    printf("and ");
    printf("%s ", adjective[0]);
    free(adjective[0]);
    printf("person that I know and you know its %s!\n",strBoolean);


    free(buff);
    free(adjective);
    free(strBoolean);

    return 0;
}


