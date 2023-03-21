#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* main - sample `ls` command
* @argc: number of arguments passed to program
* @argv: array of strings of args
* Return: 0 for success, 1 for error
*/


int main(int argc, char *argv[])
{
	struct dirent *dp;
	DIR *dir;

	if (argc < 2)
	{
	/* no arguments provided, open current directory */
		dir = opendir(".");
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_name[0] != '.')
				printf("%s\n", dp->d_name);
		}
	} else
	{
	/* print contents of directories and files given as arguments */
		for (int i = 1; i < argc; i++)
		{
			dir = opendir(argv[i]);
			if (dir == NULL)
			{
				/* argument is a file, print its name */
				printf("%s\n", argv[i]);
			} else
			{
				/* argument is a directory, print its contents */
				printf("%s:\n", argv[i]);
				while ((dp = readdir(dir)) != NULL)
				{
					if (dp->d_name[0] != '.')
						printf("%s\n", dp->d_name);
				}
				closedir(dir);
			}
		}
	}
	return (0);
}

