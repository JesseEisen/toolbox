
//
// file_read.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "file_read.h"

#define ONEK  1024

size_t
file_size(FILE *stream){
    size_t size = 0;
    fseek(stream, 0, SEEK_END);
    size = ftell(stream);
    rewind(stream);
    return size;
}

char *
file_read(const char *filename){
    FILE * fp = fopen(filename, "r");
    size_t len = file_size(fp);

    char *buf = malloc(len+1);
    if(!buf) return NULL;

    size_t read = fread(buf,sizeof(char),len, fp);

    fclose(fp);
    buf[read] = '\0';
    return buf;
}

char *
read_until_eof(FILE *stream) {
    off_t len = 0;
    char buf[ONEK];
    char *str = malloc(1);
    assert(str);

    while(!feof(stream) && !ferror(stream)){
        size_t n = fread(buf,1,1024,stream);
        len += strlen(buf);
        str = realloc(str,len);
        strncat(str,buf,n);
    }
    printf("%d\n",strlen(str));
    return str;
}
