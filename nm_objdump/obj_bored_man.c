#include <elf.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - entry point made easy because upset
 * @argc: count
 * @argv: vector
 * @envp: env array
 * Return: 0 success, 1 error
*/

int main(int argc, char **argv, char **envp)
{
	char *args[] = {"/usr/bin/objdump", "-s", "-f", "", NULL};

	(void)argc;
	args[3] = argv[1];
	if (execve("/usr/bin/objdump", args, envp) == -1)
		return (perror("execve"), -1);
	return (0);
}
