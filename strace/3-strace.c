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
			break;
	}
	return (1);
}

void print_regs(struct user_regs_struct regs)
{
	unsigned long params[6] = {0};
	size_t nb_params = 0, i;

	params[0] = (unsigned long)regs.rdi;
	params[1] = (unsigned long)regs.rsi;
	params[2] = (unsigned long)regs.rdx;
	params[3] = (unsigned long)regs.rcx;
	params[4] = (unsigned long)regs.r8;
	params[5] = (unsigned long)regs.r9;

	/* retrieve specific nb_params according to each syscall */
	nb_params = syscalls_64[(unsigned long)regs.orig_rax].nb_params;
	for (i = 0; i < nb_params; i++)
	{
		if (i > 0)
			fprintf(stdout, ",");
		if (syscalls_64[(unsigned long)regs.orig_rax].params[i] == VARARGS)
			fprintf(stdout, "...");
		else if (syscalls_64[(unsigned long)regs.orig_rax].params[i] != VOID)
			fprintf(stdout, "%#lx", params[i]);
	}
}

int tracer(pid_t child)
{
	int status;
	struct user_regs_struct regs;

	waitpid(child, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	if (step_sys(child) != 0)
		return (0);
	ptrace(PTRACE_GETREGS, child, 0, &regs);
	if (step_sys(child) != 0)
		return (0);
	ptrace(PTRACE_GETREGS, child, 0, &regs);
	fprintf(stdout, " = %#lx\n", (unsigned long)regs.rax);
	while (1)
	{
		if (step_sys(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, "%s(", syscalls_64[regs.orig_rax].name);
		print_regs(regs);
		if (step_sys(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, ") = %#lx\n", (unsigned long)regs.rax);
	}
	fprintf(stdout, ") = ?\n");
	return (0);
}

/**
 *
 *
 */

int main(int argc, char *argv[], char *envp[])
{
	pid_t child;

	if (argc < 2)
		return (fprintf(stderr, "%s [path_to_bin]", argv[0]));

	child = fork();
	++argv;
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[0], argv, envp));
	}
	else
	{
		setbuf(stdout, NULL);
		fprintf(stdout, "execve(%p, %p, %p)", (void *)argv[0],
				(void *)argv, (void *)envp);
		return (tracer(child));
	}
}
