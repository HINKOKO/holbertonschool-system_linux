bits 64

	global asm_putc ; export the function

	section .text

	; size_t asm_putc(int c);
	; prints a single character on the stdout

asm_putc:
	push rbp
	mov rbp, rsp ; stack frame set_up (ENTER)

	push rsi
	push rdi
	push rdx
	push rax

	mov rax, 1 ; syscall write
	mov rdi, 1 ; write the char
	mov rsi, rsp ; move rsi to address of top stack (where chars written)
	mov rdx, 1 ; count the byte

	syscall ; perform the system call to write

	pop rax
	pop rdx
	pop rdi
	pop rsi ; restore registers

	mov rsp, rbp
	pop rbp ; restore stack frame

	ret
