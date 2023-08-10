#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <syscall.h>
#include <sys/ptrace.h>

int main(int argc, char **argv, char **envp)
{
	pid_t child;
	int retval;
	char *args[] = {argv[1], NULL};

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

	do {
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		wait(&retval);
		printf("Single step\n");
		ptrace(PTRACE_SINGLESTEP, child, 0, 0);
	} while (!WIFEXITED(retval));
	printf("Exited with status: %d\n", WEXITSTATUS(retval));

	return (0);
}



// else
// {
// 	int child_status;
// 	ptrace(PTRACE_SYSCALL, child, NULL, NULL);
// 	/* parent here */
// 	// wait(&child_status);
// 	while (wait(&child_status) && !WIFEXITED(child_status))
// 	{
// 		printf("Single step\n");
// 		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
// 		ptrace(PTRACE_SYSCALL, child, NULL, NULL);
// 	}
// 	if (WIFEXITED(child_status))
// 		printf("Exit status: %d\n", WEXITSTATUS(child_status));
// }
