BITS 64

global asm_strlen ; export the function

asm_strlen:
	push rbp ; Setup stack frame
	mov rbp, rsp ; these two lines equivalent to ENTER

	mov r9, 0h ; initialize counter to 0

asm_loop:
	cmp byte [rdi + r9], 0h ; compare with \0 null byte (end of string)
	je asm_end ; exit and jump to the end
	inc r9 ; increment counter
	jmp asm_loop ; loop again

asm_end:
	mov rax, r9 ; put the value of counter to return I/O register rax
	mov rsp, rbp ; clean up the stack frame
	pop rbp 
	ret
