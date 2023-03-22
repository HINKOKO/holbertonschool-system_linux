#include "hls.h"

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
			col = 1;
	}
}
