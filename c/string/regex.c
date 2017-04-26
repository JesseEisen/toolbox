
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


/*
 * test the string whether match the pattern,
 * if matched, return the first result,
 * else return NULL
 */
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


char ** 
gregex(char *string, char *pattern, int cflags){
    int         i = 0, len;
    char        *p = string;
    char        **res;
    regex_t     re;
    regmatch_t  match;

    if(regcomp(&re, pattern, cflags) != 0) exit(1);

    res = malloc(sizeof(char *));
    while(regexec(&re, p, 1, &match, 0) == 0){
        len = match.rm_eo - match.rm_so;
        res[i] = malloc(len+1);
        memcpy(res[i++], &p[match.rm_so],len);
        *(res[i-1]+len) = '\0';
        p += match.rm_eo;
        res = realloc(res,sizeof(char *)*(i+1));
    }
    
    res[i] = NULL;
    regfree(&re);
    return res;
}

int 
main(void){
    char *pattern = "[1-9][0-9]*";
    char *string_pat = "(\"[a-z]+\")";
    char *string_num = "([1-9][0-9]*)" "," "\"([^\"]*)\"";
    char *string = "123,\"hello\",456,\"world\"";
    char **res;
    int i = 0;

    res = gregex(string,pattern, REG_EXTENDED);
    while(res[i] != NULL){
        printf("%s\n",res[i]);
        i++;
    }

    int j;
    for(j = 0; j < i; j++){
        free(res[j]);
    }
    free(res);
    return 0;
}
