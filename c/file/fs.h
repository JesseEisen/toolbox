#ifndef _FS_H_
#define _FS_H_

FILE * fs_open(const char *path, const char *flags);
int    fs_close(FILE *file);
size_t fs_size(const char *path);
size_t fs_fsize(FILE *file);
char * fs_read(const char *path);
char * fs_nread(const char *path, int len);
char * fs_fread(FILE * file);
char * fs_fnread(FILE *file, int len);
int    fs_write(const char *path, const char *buffer);
int    fs_nwrite(const char *path, const char *buffer, int len);
int    fs_fwrite(FILE *file, const char *buffer);
int    fs_fnwrite(FILE *file, const char *buffer, int len);


#endif
