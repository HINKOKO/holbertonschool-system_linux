#ifndef __STRACEHIM__
#define __STRACEHIM__

/* use of papamuziko */
#include "syscalls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/reg.h>

/* utility for arguments retrieving in registers */
unsigned long syscall_args(struct user_regs_struct regs, int i);


#endif /* __STRACEHIM__ */
