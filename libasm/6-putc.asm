bits 64

	global asm_putc ; export the function

	section .text

	; size_t asm_putc(int c);
	; prints a single character on the stdout

	; write syscall expects the following args
	; => rax (syscall number) set to 1
	; => rdi (file descriptor) set to 1 for stdout
	; => rsi (buffer pointer) set to address of character to be written
	; => rdx (buffer size) set to 1 , to specify hey we write a single char (1 byte)

asm_putc:
	push rbp
	mov rbp, rsp ; stack frame set_up (ENTER)

	push rdi ; strange output otherwise (PLD)
	mov rax, 1 ; syscall write 1
	mov rdi, 1 ; set to 1 stdout
	mov rsi, rsp ; set to address of char to be written (top stack)
	mov rdx, 1 ; set to 1, hey we write one char (1 byte)
	syscall ; perform the system call write

	pop rdi ; restore registers
	mov rsp, rbp
	pop rbp ; restore stack frame

	ret
