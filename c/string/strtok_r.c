
//
// strtok_r.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **
split(char *raw, const char *delim, int *len){
    char *token, *saveptr;
    char **res;
    int i = 0;

    res = malloc(sizeof(char *)*1);
    
    for(;;raw = NULL){
        token = strtok_r(raw, delim, &saveptr);
        if(token == NULL) break;
        res[i++] = token;
        res = realloc(res, sizeof(char *) * (i+1));
    }

    *len = i;
    return res;
}

int 
main(void){
    char str[] = "1,22,333,4444,55555";
    char **res;
    int len, i;

    res = split(str,",",&len);
    for(i = 0; i< len; i++){
        printf("%s\n",res[i]);
    }

    free(res);
    return 0;
}

