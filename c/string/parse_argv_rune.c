
//
// parse_argv_rune.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *argv0;
typedef unsigned int Rune;

int chartorune(Rune *, char *);

#define SET(x)    ((x)=0)
#define USED(x)    if(x); else
#define Bit(i)    (7-(i))
#define T(i)      (((1 << (Bit(i)+1))- 1)^0xFF)
#define RuneX(i)  ((1 << (Bit(i) + ((i) -1) *Bitx)) -1)


#define ARGBEGIN for((argv0||(argv0=*argv)),argv++,argc--; \
                argv[0]&& argv[0][0] == '-' && argv[0][1]; \
                argc--,argv++) { \
                    char *_args, *_argt;\
                    Rune _argc; \
                    _args = &argv[0][1]; \
                    if(_args[0] == '-' && _args[1] == 0) {\
                        argc--; argv++; break;\
                    }\
                    _argc = 0; \
                    while(*_args && (_args += chartorune(&_argc, _args)))\
                    switch(_argc)
#define ARGEND  SET(_argt); USED(_argt); USED(_argc);USED(_args); } USED(argv);USED(argc);
#define ARGF()   (_argt=_args, _args="", \
                 (*_argt? _argt:argv[1]?(argc--, *++argv): 0))

enum
{
    UTFmax      = 4,        /* maximum bytes per rune */
    Runesync    = 0x80,     /* cannot represent part of a UTF sequence (<) */
    Runeself    = 0x80,     /* rune and UTF sequences are the same (<) */
    Runeerror   = 0xFFFD,   /* decoding error in UTF */
    Runemax     = 0x10FFFF, /* 21-bit rune */
    Runemask    = 0x1FFFFF, /* bits used by runes (see grep) */
};

enum {
    Bitx = Bit(1),
    Tx   = T(1),
    Rune1 = (1 << (Bit(0)+0*Bitx))-1,
    Maskx = (1 << Bitx) -1,
    Testx = Maskx ^ 0xFF,

    SurrogateMin = 0xD800,
    SurrogateMax = 0xDFFF,

    Bad = Runeerror,

};

int 
chartorune(Rune *rune, char *str){
    int c[UTFmax], i;
    Rune l;

    c[0] = *(unsigned char *)(str);
    if(c[0] < Tx){
        *rune = c[0];
        return 1;
    }
    l = c[0];

    for(i = 1; i< UTFmax; i++){
        c[i] = *(unsigned char *)(str+i);
        c[i] ^= Tx;
        if(c[i] & Testx)
            goto bad;
        l = (l << Bitx) | c[i];
        if(c[0] < T(i + 2)) {
            l &= RuneX(i + 1);
            if(i == 1) {
                if(c[0] < T(2) || l <= Rune1) 
                    goto bad;
            }else if(l <= RuneX(i) || l > Runemax)
                goto bad;
            if(i == 2 && SurrogateMin <= l && l <= SurrogateMax)
                goto bad;
            *rune = l;
            return i + 1;
        }
    }
bad:
    *rune = Bad;
    return 1;
}

void 
usage(void){
    printf("usage: argv_parse.c [a|b|c]\n");
    exit(1);
}


int
main(int argc, char **argv){
    
    char *m; 

    ARGBEGIN {
        case 'a':
            printf("a is set\n");
            m = ARGF();
            printf("argument is %s\n",m);
            break;
        case 'b':
            printf("b is set\n");
            break;
        case 'c':
            printf("c is set\n");
            break;
        default:
            usage();
        }ARGEND

    return 0;


}
