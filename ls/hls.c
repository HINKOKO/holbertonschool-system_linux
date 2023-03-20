#include <stdio.h>
#include <dirent.h>
#include <stddef.h>

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
	struct dirent *dp;

	if (argc < 2)
	{
		/* no directory specified, use the current one*/
		dir = opendir(".");
	}
	else
	{
		/* use the specified directory */
		dir = opendir(argv[1]);
	}

	if (dir == NULL)
	{
		/* unable to open dir  */
		perror("opendir");
		return (1);
	}

	while ((dp = readdir(dir)) != NULL)
		printf("%s\n", dp->d_name);

	closedir(dir);

	return (0);
}
