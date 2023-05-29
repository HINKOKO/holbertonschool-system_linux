# **x86 Assembly - libASM**

## **Learnings**

- **The differences between Intel and AT&T syntaxes**

  The main differences between the two's lies in the way **instructions** and **operands** are written and represented <br>

  - **Operand order**
    In the AT&T Syntax , the **source comes before the destination** <br>
    In the **Intel** syntax, the **destination comes before the source.**

  - **Register prefixed**
    At&T => registers are denoted with a **%** symbol before register name
    Intel => no specific prefix, just the register name

  - **Immediate values**
    AT&T => immediate value are preceded by a **$** symbol
    Intel => no specific prefix, just the immediate value to move

  - **Memory addressing**
    AT&T => Memory operands enclosed between **parenthesis**
    Intel => Memory operands specified using **brackets**

- **The different x86 GPR**
- **The different flag registers**
- **What is a stack frame**

  Some veterans could say to you **_"hey kiddo, we don't say a stack frame, we say an activation record_**
  Anyway, **Stack frame** is used to manage function call and associated local variables, function arguments, return addresses <br>
  and preserved registers.
  => It provides a structured organization of data on the runtime **stack** for **each function invocation**
  => When a function is called, a new stack frame is created to hold the function execution's context.

- **How to setup a stack frame**
- **How to call a function**
- How to make a system call
- How to pass parameters to a function
- How to retrieve parameters
