#include "hls.h"

/**
 * main - entry point of custom 'ls'
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 for success (always success haha)
 */

int main(int argc, char *argv[])
{
	int op[4] = {0, 0, 0, 0};
	opt_t *nodes = NULL, *head = NULL;

	nodes = args_cooking(argc, argv, op);
	head = nodes;

	display_dir(head, op);

	free_list(head);
	return (0);
}
