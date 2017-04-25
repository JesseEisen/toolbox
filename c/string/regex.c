
//
// regex_r.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#define ERRORLEN 200
#define BUFLEN   100
#define M_SIZE   32

char *
regex(char *string, char *pattern, int flags){
    int     result;
    int     i,len;
    char    error[ERRORLEN];
    char    *res;
    regex_t comp;

    result = regcomp(&comp, pattern,flags);
    if(result){
        regerror(result,&comp,error,ERRORLEN);
        regfree(&comp);
        printf("error in comp:%s\n", error);
        return NULL;
    }

    regmatch_t m[M_SIZE];
    result = regexec(&comp,string,M_SIZE,m ,0);
    if(result){
        regerror(result,&comp,error,ERRORLEN);
        regfree(&comp);
        printf("error in comp:%s\n", error);
        return NULL;
    }
    
    len = m[0].rm_eo - m[0].rm_so;
    res = malloc(len+1);
    memcpy(res,&string[m[0].rm_so],len);

    regfree(&comp);
    return res;
}


int 
main(void){
    char *pattern = "([1-9][0-9]*)";
    char *string = "123,\"hello\",456";

    printf("%s\n",regex(string, pattern, REG_EXTENDED));

    return 0;

}
