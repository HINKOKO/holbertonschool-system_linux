#include "hls.h"

/**
 * args_cooking - cook the args to retrieve the options
 * passed to our custom ls
 * @argc: argument count
 * @argv: argument vector
 * @opt: options array
 * Return: a linked list with each argument in a node
 */

opt_t *args_cooking(int argc, char *argv[], int *opt)
{
	int i = 1, j = 1;
	opt_t *nodes = NULL;

	while (i < argc)
	{
		if (argv[i][0] == '-' && _strlen(argv[i]) > 1)
		{
			j = 1;
			while (_strlen(argv[i]) > j)
			{
				switch (argv[i][j])
				{
				case '1':
					opt[0] = 1;
					break;
				case 'l':
					opt[1] = 1;
					break;
				case 'a':
					opt[2] = 1;
					break;
				case 'A':
					opt[3] = 1;
					break;
				default:
					break;
				}
				j++;
			}
		}
		else
			nodes = add_node(&nodes, argv[i]);
		i++;
	}
	return (nodes);
}
