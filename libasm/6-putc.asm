bits 64

	global asm_putc ; export the function

	section .text

	; size_t asm_putc(int c);
	; prints a single character on the stdout

asm_putc:
	push rbp
	mov rbp, rsp ; stack frame set_up (ENTER)

	push rdi ; save register if were in use

	mov rax, 1 ; syscall write
	mov rdi, 1 ; write the char
	mov rsi, rsp ; source pointer to address to stack
	mov rdx, 1 ; count the char written
	syscall ; perform the system call to write

	mov rsp, rbp
	pop rbp ; restore stack frame

	ret
