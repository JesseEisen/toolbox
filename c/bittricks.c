
//
// bits_trick.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void lower_to_upper(char *letter, int len){
	int i = 0; 

	for(i; i<len; i++){
		printf("%c ", letter[i] | ' ');
	}

	printf("\n");
}


void upper_to_lower(char *letter, int len){
	int i = 0; 

	for(i; i<len; i++){
		printf("%c ", letter[i] & '_');
	}

	printf("\n");
}

void convert_case(char *letter, int len){
	int i = 0;

	for(i;i < len; i++){
		printf("%c ", letter[i] ^ ' ');
	}

	printf("\n");
}

void  find_position(char *letter, int len){
	int i = 0;

	for(i; i < len; i++){
		printf("%c is at position %d \n", letter[i], (letter[i] & 31));
	}
}


int main(void){

	char letter[] = {'a','z','h','B','D','J'};
	int len = sizeof(letter)/sizeof(letter[0]); 
    int i = 0;
	
	printf("Raw letters are:\n");
	for(i; i< len; i++){
		printf("%c ",letter[i]);
	}
	printf("\n----------------------\n\n");

	lower_to_upper(letter,len);
	upper_to_lower(letter,len);
	convert_case(letter,len);
	find_position(letter,len);

	return 0;
}
