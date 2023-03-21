#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* list_dir - function utility for listing directory
* @path: path to the directory / or file to display
*/

void list_dir(const char *path)
{
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		perror("");
		return;
	}
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
			printf("%s\t", entry->d_name);
	}
	printf("\n");
	closedir(dir);
}

/**
* main - sample `ls` command
* @argc: number of arguments passed to program
* @argv: array of strings of args
* Return: 0 for success, 1 for error
*/


int main(int argc, char *argv[])
{
	int i;

	if (argc < 2)
		list_dir(".");

	for (i = 0; i < argc; i++)
	{
		if (i > 0)
		{
		printf("%s:\t", argv[i]);
		list_dir(argv[i]);
		printf("\n");
		}
	}
	return (0);
}


