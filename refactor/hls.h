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

int main(int argc, char *argv[]);


char** handle_flags(int argc, char *argv[], int *opts);
void add_files(const char *file);

void print_1(char *read, int *options);
void print_classic(struct dirent *read);



void show_dir(char *files[], int num_files, int *options);
void show_options(char *files[], int count, int *options);





#endif
