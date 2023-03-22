#include "hls.h"

/**
* list_dir - function utility for listing directory
* @path: path to the directory / or file to display
* @display_dirname: flag for hidding directory name in the output
* @dirname: parameter to handle directory names if present
* @col: flag to switch col/tabs if option inputed or not
*/

void list_dir(const char *dirname, const char *path, int display_dirname,
int col)
{
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "./hls_01: cannot access %s: ", path);
			perror("");
		}
		else if (errno == EACCES)
		{
			fprintf(stderr, "./hls_01: cannot open directory %s: ", path);
			perror("");
		}
		else
			printf("%s\t", path);
		return;
	}
	if (display_dirname)
		printf("%s:\n", dirname);

	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
		{
			if (col)
			{
				printf("%s\n", entry->d_name);
			}
			else
				printf("%s\t", entry->d_name);
		}
	}

	printf("\n\n");
	closedir(dir);
}

/**
* args_cooking - helper function to handle option in command
* @argc: number of arguments passed to program
* @argv: array of strings of args
* @col: flag to switch the display, col or tabs
*/

void args_cooking(int argc, char *argv[], int *col)
{
	int i;

	for (i = 1; i < argc; i++)
	{
		if (_strcmp(argv[i], "-1") == 0)
			*col = 1;
	}
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
	int col = 0;

	args_cooking(argc, argv, &col);

	if (argc == 1)
		list_dir(".", ".", 0, col);
	else if (argc == 2)
		list_dir(argv[1], argv[1], 0, col);
	else
	{

		for (i = 1; i < argc; i++)
		{
			if (_strcmp(argv[i], "-1") == 0)
				continue;

			if (lstat(argv[i], &st) == -1)
			{
				fprintf(stderr, "./hls_01: cannot access %s: ", argv[i]);
				perror("");
				continue;
			}
			else
			{
				if (S_ISDIR(st.st_mode))
					list_dir(argv[i], argv[i], 1, col);
				else
					printf("%s\t", argv[i]);
			}
		}
	}
	return (0);
}

/**
* _strcmp - self strcmp to avoid not allowed function
* @s1: string 1 to be compared
* @s2: string 2 to be compared
* Return: 0 success, 1 failure
*/

int _strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;

	while (s1[j] != '\0')
		i++;
	while (s1[i] == s2[i] && i < j)
		j++;
	return (s1[i] - s2[i]);
}


