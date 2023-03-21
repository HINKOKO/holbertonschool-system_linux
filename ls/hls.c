#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

/**
* list_dir - function utility for listing directory
* @path: path to the directory / or file to display
* @display_dirname: flag for hidding directory name in the output
*/

void list_dir(const char *path, int display_dirname)
{
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		fprintf(stderr, "./hls_01: cannot access %s: %s\n", path, strerror(errno));
		return;
	}
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
		{
			if (display_dirname)
				printf("%s", path);
			printf("%s\t", entry->d_name);
		}
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
	struct stat st;

	for (i = 1; i < argc; i++)
	{
		if (lstat(argv[i], &st) == -1)
		{
			fprintf(stderr, "./hls_01: cannot access %s: %s\n", argv[i],
			strerror(errno));
			continue;
		}
		if (S_ISDIR(st.st_mode))
			list_dir(argv[i], argc > 2);
		else
			printf("%s\t", argv[i]);
	}

	if (argc == 1)
		list_dir(".", 0);

	return (0);
}


