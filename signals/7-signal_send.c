#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/**
 * main - send the signal SIGINT to a process
 * given its PID (using kill(pid, signal))
 * @argc: argument count
 * @argv: argument vector
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf(stderr, "Usage: %s <pid>", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (kill(atoi(argv[1]), SIGINT) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
