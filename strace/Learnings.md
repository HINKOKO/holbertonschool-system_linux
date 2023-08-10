# **LEarnings from this project**

- **What is strace, and what is its purpose**

  According to man page, **strace** is a tool that one can use to trace all the system calls made by a running process. Once attached to a running process, **strace** is able to intercept the system calls that are called by this process, and reveal all the information about them. **strace** is also able to intercept signals received by the process being traced.

- **What is ptrace, and what possibilities it offers**

  **ptrace** system call is a powerful debugging and tracing mechanism on Linux that allows one process -- called the <i>tracer</i> -- to control/examine the execution of another process -- called the <i>tracee</i> -- and even change the tracee's memory and registers ! <br>
  It is primarily used to implement breakpoint debugging and system call tracing (like in **gdb** for example)

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
