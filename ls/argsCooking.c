#include "hls.h"

/**
 * opts_finder - helper function to find if options are passed
 * @argc: number of args
 * @argv: array of args
 * Return: options array
*/

char *opts_finder(int argc, char *argv[])
{
	int i, a, b = 0, count = 0;
	char *opts = NULL;

	for (i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			for (a = 1; argv[i][a] != '\0'; a++)
				count++;
		}
	}

	if (count)
	{
		opts = malloc(count + 1);
		for (i = 0; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				for (a = 1; argv[i][a] != 0; a++)
				{
					opts[b] = argv[i][a];
					b++;
				}
			}
		}
		opts[b] = '\0';
	}
	return (opts);
}
