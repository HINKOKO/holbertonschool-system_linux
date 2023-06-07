#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/**
 * main - program that takes a 'signum' as argument
 * and display basic info about that signal
 * @argc: argument count
 * @argv: argument vector
 * Return: 1 on Error with error message, success another int
 */

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (printf("%s: %s\n", argv[1], strsignal(atoi(argv[1]))));
}
