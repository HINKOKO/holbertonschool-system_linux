#include "strace.h"

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
	size_t nb_params = 0, i;
	unsigned long params[6] = {
		regs.rdi,
		regs.rsi,
		regs.rdx,
		regs.rcx,
		regs.r8,
		regs.r9,
	};

	/* retrieve specific nb_params according to each syscall */
	nb_params = syscalls_64[regs.orig_rax].nb_params;
	for (i = 0; i < nb_params; ++i)
	{
		if (i > 0)
			fprintf(stdout, ",");
		if (syscalls_64[regs.orig_rax].params[i] != VOID)
		{
			if (syscalls_64[regs.orig_rax].params[i] == VARARGS)
				fprintf(stdout, "...");
			else
				fprintf(stdout, "%#lx", (unsigned long)params[i]);
		}
	}
}

int tracer(pid_t child)
{
	int status;
	struct user_regs_struct regs;

	/* disable buffering */
	setbuf(stdout, NULL);

	waitpid(child, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	if (step_sys(child) != 0)
		return (0);
	ptrace(PTRACE_GETREGS, child, 0, &regs);
	while (1)
	{
		if (step_sys(child) != 0)
			break;
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, "%s(", syscalls_64[regs.orig_rax].name);
		print_regs(regs);
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
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[1], argv, envp));
	}
	else
		return (tracer(child));
}
