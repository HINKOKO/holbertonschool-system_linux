#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <asm/unistd_64.h>

int main(int argc, char **argv, char **envp)
{
	pid_t child;
	int retval;
	unsigned long sysnum = 0;
	char *args[] = {argv[1], NULL};
	struct user_regs_struct regs;

	if (argc < 2)
		printf("bad usage michael\n"), exit(EXIT_FAILURE);

	child = fork();
	if (child == -1)
		fprintf(stderr, "failed to fork"), exit(-1);
	if (child == 0)
	{
		/* sweet child o'mine */
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		if (execve(argv[1], args, envp) < 0)
		{
			perror("execve");
			return (1);
		}
	}
	wait(&retval);
	while (WIFSTOPPED(retval)) {
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		wait(&retval);
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		sysnum = regs.orig_rax;
		printf("%lu\n", sysnum);
		/* continue execution of child process */
		ptrace(PTRACE_SYSCALL, child, 0, 0);
	}
	printf("Exit status: %d\n", WEXITSTATUS(retval));
	return (0);
}
