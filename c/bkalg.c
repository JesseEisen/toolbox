
//
// bit.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>

/*
 * Brain Kernighan's count integer set bits
 */
int
bit_count_set(int n){

	int count = 0;

	for(; n; count++){
		n = n & (n - 1);
	}

	return count;
}

#define TEST
#ifdef TEST

#define FMT "\x1B[3%dm%s -- %s\033[0m \n"
#define LOG(res,fmt,...) ({    \
	char *str = malloc(1024); \
	if(res == 2){ \
		sprintf(str,fmt,__VA_ARGS__); \
		printf(FMT,res,"Pass",str);\
	}else{\
		sprintf(str,fmt,__VA_ARGS__); \
		printf(FMT,res,"Error",str);\
	}	\
})

int
main(void){
	int neg_number[] = {-1, -127,-128,-2147483647};
	int neg_expect[] = {32,26,25,2};
	int pos_number[] = {0,1,65535,2147483647};
	int pos_expect[] = {0,1,16,31};

	int i,res;
	for(i = 0; i<4; i++){
		if(neg_expect[i] == (res=bit_count_set(neg_number[i]))){
			LOG(2,"number %d bits set are %d",neg_number[i], neg_expect[i]);
		}else{
			LOG(1,"number %d bits set are %d, expected %d", neg_number[i], res, neg_expect[i]);
		}

		if(pos_expect[i] == (res=bit_count_set(pos_number[i]))){
			LOG(2,"number %d bits set are %d",pos_number[i], pos_expect[i]);
		}else{
			LOG(1,"number %d bits set are %d, expected %d", pos_number[i], res, pos_expect[i]);
		}

	}
}

#endif  //TEST
