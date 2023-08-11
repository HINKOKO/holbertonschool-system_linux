#include "strace.h"

/**
 * main - executes an trace a given command in argv[1]
 * @argc: argument count
 * @argv: argument vector
 * @envp: env string array
 * Return: 0 success, -1 on failure
 */

int main(int argc, char *argv[], char *envp[])
{
	int status = 0, flag = 0;
	pid_t child;
	struct user_regs_struct regs;

	if (argc < 2)
		return (fprintf(stderr, "%s [path_to_command]\n", argv[0]), -1);

	setbuf(stdout, NULL);
	child = fork();
	if (child < 0)
		return (fprintf(stderr, "Failed to fork"), -1);
	else if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		kill(getpid(), SIGSTOP);
		execve(argv[1], &(argv[1]), envp);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (0);
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		while (wait(&status) && !WIFEXITED(status))
		{
			memset(&regs, 0, sizeof(regs));
			ptrace(PTRACE_GETREGS, child, 0, &regs);
			if (flag)
				printf(" = %#lx\n", (unsigned long)regs.rax), flag = 0;
			if (WSTOPSIG(status) == SIGTRAP && (long)regs.rax == -38)
				printf("%s", (char *)syscalls_64[regs.orig_rax].name), flag = 1;
			ptrace(PTRACE_SYSCALL, child, 0, 0);
		}
		printf(" = ?\n");
	}
	return (0);
}
