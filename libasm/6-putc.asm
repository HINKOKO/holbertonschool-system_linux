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


	mov rax, 1 ; syscall write
	mov rdi, 1 ; write the char
	mov rsi, rsp ; set to the address of character to be written
	mov rdx, 1 ; count the char written
	syscall ; perform the system call to write

	mov rsp, rbp
	pop rbp ; restore stack frame

	ret
