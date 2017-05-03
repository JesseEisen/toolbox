
//
// fs.c
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "fs.h"

#define FS_OPEN_READ "r"
#define FS_OPEN_WRITE "w"
#define FS_OPEN_READWRITE "rw"


FILE *
fs_open(const char *path, const char *flags){
	return fopen(path,flags);
}

int
fs_close(FILE *file){
	return fclose(file);
}

size_t
fs_size(const char *path){
	size_t size;
	FILE * file = fs_open(path, FS_OPEN_READ);
	if (NULL == file) return -1;
	fseek(file, 0, SEEK_END);
	size= ftell(file);
	fs_close(file);
	return size;
}

/*
 * now file is opend, so need to save current position
 */
size_t 
fs_fsize(FILE *file){
	unsigned long pos = ftell(file);
	rewind(file);
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file,pos,SEEK_SET);
	return size;
}


char *
fs_fnread(FILE *file, int len){
	char * buffer = malloc(sizeof(char) * (len + 1));
	fread(buffer,1,len,file);
	buffer[len] = '\0';
	return buffer;
}

char *
fs_fread(FILE *file){
	size_t fsize = fs_fsize(file);
	return fs_fnread(file, fsize);
}

char *
fs_read(const char *path){
	FILE *file = fs_open(path, FS_OPEN_READ);
	if(NULL == file) return NULL;
	char *data = fs_fread(file);
	fs_close(file);
	return data;
}

char *
fs_nread(const char *path, int len){
	FILE *file = fs_open(path, FS_OPEN_READ);
	if(NULL == file) return NULL;
	char *data = fs_fnread(file,len);
	fs_close(file);
	return data;
}

int 
fs_fwrite(FILE * file, const char *buffer){
	return fs_fnwrite(file,buffer, strlen(buffer));
}

int 
fs_fnwrite(FILE *file, const char *buffer, int len){
	return (int) fwrite(buffer, 1, len, file);
}

int 
fs_write(const char *path, const char *buffer){
	return fs_nwrite(path,buffer,strlen(buffer));
}

int
fs_nwrite(const char *path, const char *buffer, int len){
	FILE *file = fs_open(path, FS_OPEN_WRITE);
	if(NULL == file) return -1;
	int result = fs_fnwrite(file,buffer, len);
	fs_close(file);
	return result;
}


