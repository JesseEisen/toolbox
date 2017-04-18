
//
// asprintf.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>

#include "asprintf.h"

int 
asprintf(char **str, const char *fmt, ...) {
	int size = 0;
	va_list args = {{0}};

	va_start(args, fmt);
	size = vasprintf(str,fmt,args);

	va_end(args);

	return size;
}

int 
vasprintf(char **str, const char *fmt, va_list args){
	int size = 0;
	va_list tmpa = {{0}};

	/*init variadic arguments*/
	va_copy(tmpa, args);

	/*get size of arguments*/
	size = vsnprintf(NULL,size, fmt,tmpa);

	va_end(tmpa);

	if(size < 0) {return -1;}

	/*alloc with size plus 1 for '\0'*/
	*str = (char *)malloc(size + 1);
	if(NULL == *str) {return -1;}

	/*
	 * format string with original, now 
	 * the size is enough and not be truncated
	 */
	size =vsprintf(*str, fmt, args);
	return size;
}

