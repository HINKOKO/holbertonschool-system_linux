#include "hls.h"

/**
 * 
 * 
 * 
 * 
*/

void print_1(char *read, int *options)
{
	if (options[0] == 1) printf("%s\n", read);
	else printf("%s ", read);
}

/**
 * 
 * 
 * 
 * 
*/

void print_classic(struct dirent *read)
{
	struct stat st;

	lstat((*read).d_name, &st);
	printf("%s", (*read).d_name);
}
