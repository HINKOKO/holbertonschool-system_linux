#include "strace.h"

/**
 * main - executes an trace a given command in argv[1]
 * @argc: argument count
 * @argv: argument vector
 * @envp: env string array
 * Return: 0 success, 1 on failure
 */

int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	int retval = 0;
	struct user_regs_struct regs;
	unsigned long num = 0;

	if (argc < 2)
		return (fprintf(stderr, "Bad usage dude\n"), -1);

	/* create child process */
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		execve(argv[1], argv + 1, envp);
	}
	do {
		/* parent process */
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		wait(&retval);
		memset(&regs, 0, sizeof(regs));
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		if (num)
			num = 0;
		else
		{
			num = regs.orig_rax;
			printf("%ld\n", num);
		}
	} while (!WIFEXITED(retval));

	return (0);
}
