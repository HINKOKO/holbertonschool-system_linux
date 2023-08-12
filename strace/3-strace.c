#include "strace.h"
#include "syscalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/reg.h>

int step_sys(pid_t child)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) == (SIGTRAP | 0x80))
			return (0);
		if (WIFEXITED(status))
		{
			fprintf(stdout, ") = ?\n");
			return (1);
		}
	}
}

void print_regs(struct user_regs_struct regs)
{
	unsigned long params;
	int nb_params = 0, i = 0;

	/* retrieve specific nb_params according to each syscall */
	nb_params = syscalls_64[(unsigned long)regs.orig_rax].nb_params;
	for (i = 0; i < nb_params; i++)
	{
		params = syscall_args(regs, i);
		if (syscalls_64[(unsigned long)regs.orig_rax].params[i] == VARARGS)
			fprintf(stdout, "...");
		else
			fprintf(stdout, "%#lx", params);
		if (i < nb_params - 1)
			fprintf(stdout, ", ");
	}
}

void tracer(pid_t child)
{
	int status;
	struct user_regs_struct regs;

	waitpid(child, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (step_sys(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, "%s(", syscalls_64[regs.orig_rax].name);

		print_regs(regs);
		fflush(stdout);

		if (step_sys(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, ") = %#lx\n", (unsigned long)regs.rax);
	}
}

void tracee(char *const argv[], char *const envp[])
{
	ptrace(PTRACE_TRACEME);
	kill(getpid(), SIGSTOP);
	execve(argv[0], argv, envp);
}

int main(int argc, char *argv[], char *envp[])
{
	pid_t child;

	if (argc < 2)
		return (fprintf(stderr, "%s [path_to_bin]", argv[0]));

	else
	{
		child = fork();
		if (child == 0)
			tracee(argv + 1, envp);
		else if (child > 0)
			tracer(child);
		else
		{
			perror("fork");
			return (-1);
		}
	}
	return (0);
}
