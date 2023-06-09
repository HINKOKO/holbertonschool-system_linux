bits 64

	global asm_puts ; export the function
	extern asm_strlen ; import strlen

	section .text

	; prints a string of chars on stdout

asm_puts:
	push rbp;
	mov rbp, rsp ; setup stack frame

	push rdi
	call asm_strlen
	push rsi ; rsi , source index, used as a pointer to a source in stream ops
	push rdx
	mov rdx, rax ; bytes written in rdx count
	; ==> whenever we call a function or syscall, rax hold their return value
	; thus, let's move rax to rdx => the data register for I/O OPS
	mov rax, 1 ; syscall write 1
	mov rsi, rdi ; set rsi to the address of string to be written
	mov rdi, 1 ; fd 1 stdout to dest instruction I/O
	syscall

	pop rdx
	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret


