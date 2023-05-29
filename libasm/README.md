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
  Before talking about the **GPR** for **G**eneral **P**urpose **R**egisters, we have to mention registers's name won't be the same <br>
  as we refer to its 64, 32, 16, or 8 bits capacity.
  For example the RAX register (64 bits), will be referred as EAX in 32 bits (E for extended), AX for 16 bits, and AH/AL for 8 bits (AH and AL for High and Low parts)
  There are 8 **GPR** for **G**eneral **P**urpose **R**egisters that you should never forget (32-bits naming here):
  - **EAX** Main register used in arithmetic operations. Also known as **_Accumulator_**, as it holds the results of arithmetic <br>
    operations and function return values
  - **EBX** the Base register. Pointer to data in the DS Segment. Used to store the base address of the program
  - **ECX** the Counter register, often used to hold a value representing the number of times a process is to be repeated. <br>
    Used for loops and string operations
  - **EDX** a general purpose one, additionally used for I/O operations.
  - **ESI** Source Index register, holds the address from where to read data.
  - **EDI** Destination Index register, holds the implies write address of all string operations.
  - **EBP** Base pointer, pointer to data on the stack. It points to the bottom of the current **_stack frame_** (used to reference local variables)
  - **ESP** Stack pointer, points to the top of the current **_stack frame_** (used to reference local variables)
- **The different flag registers**
- **What is a stack frame**

  Some veterans could say to you **_"hey kiddo, we don't say a stack frame, we say an activation record_**
  Anyway, **Stack frame** is used to manage function call and associated local variables, function arguments, return addresses <br>
  and preserved registers.
  => It provides a structured organization of data on the runtime **stack** for **each function invocation**
  => When a function is called, a new stack frame is created to hold the function execution's context.
  A stack frame exists whenever a function has started but yet to complete.

- **How to setup a stack frame**
  In Assembly, to setup a stack frame we use the following instructions:
  ```
  push rbp ; save the previous base pointer
  mov rbp, rsp ; setup the stack pointer
  ```
  This is what we call the "prologue"
- **How to call a function**
- How to make a system call
- How to pass parameters to a function
- How to retrieve parameters
