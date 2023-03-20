#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* main - sample `ls` command
* @argc: integer, number of command line arguments
* @argv: array of strings, contains command line arguments
* passed to the program
* Return: 0 for success, 1 for error
*/


int main(int argc, char *argv[])
{
	(void) argc;
	(void) *argv;
	DIR *dir;
	struct dirent *dp;
	/* no directory specified, use the current one*/
	dir = opendir(".");
	if (dir == NULL)
	{
		/* unable to open dir  */
		printf("Error, unable to open the directory!");
		exit(1);
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.')
			printf("%s\t", dp->d_name);
	}
	printf("\n");
	closedir(dir);
	return (0);
}
