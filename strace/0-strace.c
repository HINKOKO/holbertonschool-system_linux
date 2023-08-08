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
	pid_t pid;
	int retval = 0;
	struct user_regs_struct regs;

	if (argc < 2)
		return (fprintf(stderr, "Bad usage dude\n"), -1);

	setbuf(stdout, NULL);
	/* create child process */
	pid = fork();
	if (pid == 0)
	{
		ptrace(PTRACE_TRACEME, pid, NULL, NULL);
		fclose(stdout);
		execve(argv[1], &(argv[1]), envp);
	}
	else
	{
		/* parent process here */
		wait(&retval);
		if (WIFEXITED(retval))
			return (0);
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		while (wait(&retval) && !WIFEXITED(retval))
		{
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, pid, 0, &regs);
			if (WSTOPSIG(retval) == SIGTRAP && (long)regs.rax == -38)
				printf("%lu\n", (long)regs.orig_rax);
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
	}
	return (0);
}
