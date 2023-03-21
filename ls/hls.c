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
* @dirname: parameter to handle directory names if present
*/

void list_dir(const char *dirname, const char *path, int display_dirname)
{
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		fprintf(stderr, "./hls_01: cannot access %s: \n", path);
		perror("");
		return;
	}
	if (display_dirname)
		printf("%s:\n", dirname);
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
		{
			/* if (display_dirname) */
			/* printf("%s", path); */
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

	if (argc == 1)
		list_dir(".", ".", 0);
	else if (argc == 2)
		list_dir(argv[1], argv[1], 0);
	else
	{

		for (i = 1; i < argc; i++)
		{
			if (lstat(argv[i], &st) == -1)
			{
				fprintf(stderr, "./hls_01: cannot access %s: \n", argv[i]);
				perror("");
				continue;
			}
			if (S_ISDIR(st.st_mode))
				list_dir(argv[i], argv[i], 1);
			else
				printf("%s\t", argv[i]);
		}
	}

	return (0);
}


