#include "strace.h"

/**
 * syscall_picker - Wait for a syscall and check if
 * child stopped or exited.
 * @child: pid of child
 * Return: 0 if child stopped , 1 if exited
*/

static int syscall_picker(pid_t child)
{
	int ret;

	while (98)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &ret, 0);
		if (WIFSTOPPED(ret) && WSTOPSIG(ret) & 0x80)
			return (0);
		if (WIFEXITED(ret))
			return (1);
	}

}

/**
 * trace_parent - Tracing in the parent
 * @child: pid of child process
*/

static void trace_parent(pid_t child)
{
	int ret;
	struct user_regs_struct regs;

	waitpid(child, &ret, 0);
	/* If the PTRACE_O_TRACESYSGOOD option was set by the tracer */
	/* then WSTOPSIG(status) will give the value (SIGTRAP | 0x80) */
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	while (98)
	{
		if (syscall_picker(child))
			break;
		memset(&regs, 0, sizeof(regs));
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		printf("%lu\n", (long)regs.orig_rax);
		if (syscall_picker(child))
			break;
	}
}

/**
 * trace_kid - Tracing in child process
 * @argv: array of arguments
 * @envp: array of environment variables
*/

static void trace_kid(char *argv[], char *envp[])
{
	ptrace(PTRACE_TRACEME, 0, 0, 0);
	kill(getpid(), SIGSTOP);
	if (execve(argv[1], argv + 1, envp) == -1)
	{
		fprintf(stderr, "execve failed\n");
		exit(EXIT_FAILURE);
	}
}

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

	if (argc < 2)
		return (fprintf(stderr, "Bad usage dude\n"), -1);

	/* disable buffering */
	setbuf(stdout, NULL);
	/* create child process */
	child = fork();
	if (child == -1)
	{
		fprintf(stderr, "Failed to fork");
		return (-1);
	}
	if (child == 0)
		trace_kid(argv, envp);

	/* If the PTRACE_O_TRACESYSGOOD option was set by the tracer */
	/* then WSTOPSIG(status) will give the value (SIGTRAP | 0x80) */
	else
		trace_parent(child);

	return (0);
}
