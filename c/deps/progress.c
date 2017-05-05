
//
// progress.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void 
progress(size_t count, size_t max){
    const char *prefix = "Progress: [";
    const char *suffix = "]";
    const size_t prefix_length = strlen(prefix);
    const size_t suffix_length = strlen(suffix);
    char *buffer = calloc(max + prefix_length + suffix_length + 1, 1);
    size_t i = 0;
    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = 100000000L; //0.1s
    
    strcpy(buffer,prefix);
    for(; i<max; i++){
        buffer[prefix_length + i] = i < count? '#': '-';
    }

    strcpy(&buffer[prefix_length + i], suffix);
    printf("\033[A\033[2K\r%s %d%%\n",buffer,count*10/4);
    fflush(stdout);
    nanosleep(&ts, NULL);
    free(buffer);
}

int 
main(void){
    
    int count = 0, max = 200;
    int done = 0;

    puts("\n");
    int i = 0;
    while(count <= max){
        count += 5;
        done = (((count*100/max*100)/100) * 4 )/10;
        progress(done, 40);
    }
    
    return 0;
}
