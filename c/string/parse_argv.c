
//
// parse_argv.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *argv0;

#define ARGBEGIN  for((argv0 = *argv), argv++, argc--; \
        argv[0] && argv[0][0]=='-' && argv[0][1]; \
        argc--, argv++) {\
            char * _args, *_argt, _argc;\
            _args = &argv[0][1];\
            if(_args[0] == '-' && _args[1] == 0){\
                argc--;argv++; break;\
            }\
            while(*_args) switch(_argc=*_args++)
#define ARGEND  }
#define ARGF()  (_argt = _args, _args="", \
                (*_argt? _argt: argv[1]? (argc--,*++argv): 0))


void 
usage(void){
    fprintf(stderr,"Usage: parse_argv [a|b <arg>|c]\n");
    exit(1);
}

int 
main(int argc, char **argv){
    
    char *m;

    ARGBEGIN{
        case 'a':
            printf("a is set\n");
            break;
        case 'b':
            m = ARGF();
            printf("b is set\n");
            printf("the argument is %s\n",m);
            break;
        case 'c':
            printf("c is set\n");
            break;
        default:
            usage();
    }ARGEND

    return 0;
}

