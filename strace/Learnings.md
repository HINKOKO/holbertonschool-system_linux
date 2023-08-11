# **LEarnings from this project**

- **What is strace, and what is its purpose**

  According to man page, **strace** is a tool that one can use to trace all the system calls made by a running process. Once attached to a running process, **strace** is able to intercept the system calls that are called by this process, and reveal all the information about them. **strace** is also able to intercept signals received by the process being traced.

- **What is ptrace, and what possibilities it offers**

  **ptrace** system call is a powerful debugging and tracing mechanism on Linux that allows one process -- called the <i>tracer</i> -- to control/examine the execution of another process -- called the <i>tracee</i> -- and even change the tracee's memory and registers ! <br>
  It is primarily used to implement breakpoint debugging and system call tracing (like in **gdb** for example)

  **ptrace** signature is

  ```
  long ptrace(enum __ptrace_request request, pid_t pid,
              void *addr, void *data);
  ```

  The first argument determine the 'behavior' of ptrace and how other arguments will be used. <br>
  This request has to be one of the following: PTRACE_TRACEME, PTRACE_PEEKTEXT, PTRACE_PEEKDATA, PTRACE_PEEKUSER, PTRACE_POKETEXT, PTRACE_POKEDATA, PTRACE_POKEUSER, PTRACE_GETREGS, PTRACE_GETFPREGS, PTRACE_SETREGS, PTRACE_SETFPREGS, PTRACE_CONT, PTRACE_SYSCALL, PTRACE_SINGLESTEP, PTRACE_DETACH.

==> Calling **ptrace** with **PTRACE_PEEKUSER** allows us to examine the contents of **USER** area where registers contents and other stuff is stored.

In this folder of exercises, we mostly use for request parameter of ptrace:

- **PTRACE_SYCALL**: makes the kernel stop the child process whenever a system call entry or exit is made.
  (equivalent of doing a PTRACE_CONT and stopping at the next system call entry/exit)

- **PTRACE_GETREGS** place all the registers in a single call and read their values at the time of a syscall entry/exit.

- **PTRACE_PEEKUSER** to look into the arguments of the system call entry/exit.

- **What are the differences between PTRACE_SINGLESTEP and PTRACE_SYSCALL**

#### PTRACE_SINGLESTEP

- Tracer makes the tracee executes a single instruction and pause
  If you have a look at the Concept_Page_Exercise/ folder, the difference of output between ex_0.c and ex_1.c is about 60,000 lines roughly.
- It is used to look very closely to the behavior of tracee, like a 'Max-Zoom-In'.
- We can debug very specific issues at a very fine level of detail

#### PTRACE_SYSCALL

- Is used to continue the execution of the tracee until it enters or exits a system call.
- When the tracee enters a system call, it stops, and the tracer can examine the syscall arguments or other informations.
- Useful for monitoring syscalls, or potentially modify syscall arguments or behavior, before allowing the tracee to continue.

Those two requests used with ptrace() serve different purposes.<br>
SINGLESTEP provides detailed insight into the execution flow <br>
SYSCALL provides monitoring on syscalls and potentially allow the tracer to modify syscall behavior/arguments.

- **How to read from and/or write to the memory of a process being traced**
