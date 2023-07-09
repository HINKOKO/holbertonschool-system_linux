#include "objdump.h"

/**
 * main - entry point of program
 * @argc: argument count
 * @argv: argument vector
 * Return: exit status int
*/

int main(int argc, char **argv)
{
	int i, ret;

	if (argc <= 2)
		return (objdumper(argc == 1 ? DEFAULT : argv[1]));
	ret = EXIT_SUCCESS;

	while (argc-- > 1)
	{
		printf("\n%s:\n\n", argv[i]);
		if (objdumper(argv[i++]) == 1)
			ret = EXIT_FAILURE;
	}
	return (ret);
}
