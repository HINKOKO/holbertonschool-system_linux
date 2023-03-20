#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * sample_ls - core process of ls implementation
 * @dir: the dir to open and read
 * @op_a: for option 1
 * @op_l: for option 2
*/

void sample_ls(const char *dir, int op_a, int op_l)
{
	struct dirent *d;
	DIR *dh = opendir(dir);

	if (!dh)
	{
		if (errno == ENOENT)
		{
			perror("Directory do not exists");
		}
		else
			perror("Unable to read directory");
	exit(EXIT_FAILURE);
	}

	while ((d = readdir(dh)) != NULL)
	{
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s ", d->d_name);
		if (op_l)
			printf("\n");
	}

	if (!op_l)
		printf("\n");
}

/**
* main - main function
* @argc: number of arguments passed to main
* @argv: array of strings of argument
* Return: 0 success, 1 failure
*/

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		sample_ls(".", 0, 0);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			int op_a = 0, op_l = 0;
			char *p = (char *)(argv[1] + 1);

			while (*p)
			{
				if (*p == 'a')
					op_a = 1;
				else if (*p == 'l')
					op_l = 1;
				else
				{
					perror("Option unavailable");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			sample_ls(".", op_a, op_l);
		}
	}
	return (0);
}
