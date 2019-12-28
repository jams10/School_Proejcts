#ifndef SEARCH
#define SEARCH
#define _XOPEN_SOURCE 500 
#include <ftw.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

extern int check_exist;
extern char current_file[32];

extern int check_file(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

#endif
