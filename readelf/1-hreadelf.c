#include <stdio.h>
#include <unistd.h>

/**
 * main - help to display the infos contained in the
 * ELF File Header of an ELF file
 * @argc: count of args
 * @argv: array of args
 * @envp: array of strings env
 * Return: 0 for success
 * using `whereis readelf` gives us "/usr/bin/readelf"
 * to find the program to execute
*/

int main(int argc, char **argv, char **envp)
{
	char *args[] = {"readelf", "-W", "-S", "", NULL};

	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./0-hreadelf <elf_filename>\n");
		return (1);
	}
	/* file to read the elf from is inputed at argv[1] */
	args[3] = argv[1];

	if (execve("/usr/bin/readelf", args, envp) == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}
