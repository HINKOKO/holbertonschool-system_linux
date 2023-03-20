#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* main - sample `ls` command
* @argc: number of arguments passed to program
* @argv: array of strings-arguments
* Return: 0 for success, 1 for error
*/


int main(int argc, char *argv[] __attribute__((unused)))
{
	struct dirent *entry;
	DIR *dir;

	if (argc == 1)
	{
		dir = opendir(".");
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] == '.')
				continue;
			printf("%s\n", entry->d_name);
		}
	}

	closedir(dir);
	return (0);
}
