#ifndef _FILE_READ_H_
#define _FILE_READ_H_

char * read_until_eof(FILE *);
char * file_read(const char *);
size_t file_size(FILE *);
#endif
