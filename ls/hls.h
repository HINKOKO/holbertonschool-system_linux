#ifndef MY_LS
#define MY_LS

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>

void list_dir(const char *dirname, const char *path, int display_dirname,
int col);
int main(int argc, char *argv[]);

/* about strings functions */
int _strcmp(char const *s1, char *s2);

/* for arguments manipulation */
char *opts_finder(int argc, char *argv[]);

#endif
