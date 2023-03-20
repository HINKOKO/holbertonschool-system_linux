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
DIR *dir;
struct dirent *entry;

if (argc < 2)
{
	fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
	exit(EXIT_FAILURE);
}

dir = opendir(argv[1]);

if (dir == NULL)
{
	perror("opendir");
	exit(EXIT_FAILURE);
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
