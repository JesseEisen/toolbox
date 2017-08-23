
//
// test.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_print.h"

int main(void)
{
    int code = 31;
    c_print(COLOR_RED,     "RED:%d\n",code++);
    c_print(COLOR_GREEN,   "GREEN:%d\n",code++);
    c_print(COLOR_YELLOW,  "YELLOW:%d\n",code++);
    c_print(COLOR_BLUE,    "BLUE:%d\n",code++);
    c_print(COLOR_MAGENTA, "MAGENTA:%d\n",code++);
    c_print(COLOR_CYAN,    "CYAN:%d\n",code++);
    c_print(COLOR_NORMAL,  "NORMAL:%d\n",code++);
    c_print(COLOR_MAX,  "MAX:%d\n",code++);
    return 0;
}
