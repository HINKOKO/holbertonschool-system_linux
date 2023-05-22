BITS 64
	global	asm_strcmp

asm_strcmp:
	push rbp ; set_up stack frame
	mov rbp, rsp ; 2 lines equivalent to `enter`

loop_cmp:
	movzx eax, byte [rdi] ; load 1st character 1st string zx to zero extend to 32 bits
	movzx edx, byte [rsi] ; load 1st char 2nd string zx zero extend to 32 bits

	cmp al, 0x0 ; check if reach end of strings
	je compare ; if yes , jump to compare

	cmp al, dl ; compare the characters
	jne compare ; jump to compare if different, to determine what

	inc rdi
	inc rsi ; let's move on to next characters
	jmp loop_cmp ; Repeat the loop

compare:
	cmp al, dl ; compare characters
	jl less ; jump to less if 1st string char is less
	jg greater ; jump to greater if first string char is greater

	mov rax, 0x0 ; set 0 if equality

less:
	mov rax, -0x1
	jmp out

greater:
	mov rax, 0x1
	jmp out

out:
	mov rsp, rbp ; restore the stack pointer
	pop rbp ; restore base pointer ==> clean_up stack frame
	ret
