#ifndef SAMPLE_LS
#define SAMPLE_LS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>

/* Manage argument options */
void args_cooking(int argc, char *argv[], int *col);

/* main and display directory/files logic */
int main(int argc, char *argv[]);
void list_dir(const char *dirname, const char *path, int display_dirname,
int col);

/* string utilities */
int _strcmp(char *s1, char *s2);

#endif
