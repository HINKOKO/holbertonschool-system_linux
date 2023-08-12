#include "strace.h"
#include "syscalls.h"

unsigned long syscall_args(struct user_regs_struct regs, int i)
{
	switch (i)
	{
	case 0:
		return ((unsigned long)regs.rdi);
	case 1:
		return ((unsigned long)regs.rsi);
	case 2:
		return ((unsigned long)regs.rdx);
	case 3:
		return ((unsigned long)regs.r10);
	case 4:
		return ((unsigned long)regs.r8);
	case 5:
		return ((unsigned long)regs.r9);
	default:
		return (-1UL);
	}
}
