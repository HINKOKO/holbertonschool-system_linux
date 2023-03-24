#include "hls.h"
#define MAX_FILES 24

char *flags[MAX_FILES];
int n_files = 0;

void add_files(const char *file) {
	flags[n_files++] = strdup(file);
}

/**
 * handle_args - helper function to determine what to do
 * according to the number of args
 * @argc: count of args
 * @argv: array of strings (args)
 * Return: array with dash-args positions
*/

char** handle_flags(int argc, char *argv[], int *opts)
{
	int i = 1, j = 1;

	while (i < argc)
	{
		if (argv[i][0] == '-' && _strlen(argv[i]) > 1)
		{
			j = 1;
			while (_strlen(argv[i] > j))
			{
				switch (argv[i][j])
				{
					case '1':
						opts[0] = 1;
						break;
					default:
						break;
				}
				j++;
			}
		}
		else 
		{
			add_files(argv[i]);
		}
		i++;
	}
	return (flags);
}
