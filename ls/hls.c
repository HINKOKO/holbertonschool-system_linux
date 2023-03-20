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
	struct dirent *entry;
	DIR *dir = opendir(".");

	if (dir == NULL)
	{
		printf("Error opening directory\n");
		return (1);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
	return (0);
}
