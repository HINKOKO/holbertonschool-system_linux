#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* main - sample `ls` command
* Return: 0 for success, 1 for error
*/


int main(void)
{
	struct dirent *dp;
	DIR *dir = opendir(".");

	if (dir == NULL)
	{
		perror("");
		printf("Error, unable to open the directory!");
		return (1);
	}
	while ((dp = readdir(dir)))
	{
		if (dp->d_name[0] != '.')
			printf("%s\t", dp->d_name);
	}
	printf("\n");
	closedir(dir);
	return (0);
}
