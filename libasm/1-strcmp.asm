BITS 64
	global	asm_strcmp

asm_strcmp:
	; registers in order rdi, rsi, rdx, rcx, r8, r9
	push rbp
	mov rbp, rsp ; setup
	cmp rdi, 0 ; check if arg1 is NULL
	je end
	cmp rsi, 0 ; check if arg2 is NULL
	je end
	xor rcx, rcx ; quick trick to init iterator rcx to 0

loop:
	mov r9b, [rdi + rcx] ; load one char string1
	mov r8b, [rsi + rcx] ; load one char string2
	cmp r9b, 0 ; check for end of string 1
	je compare
	cmp r8b, 0 ; check for end of string 2
	je compare
	cmp r9b, r8b ; compare chars
	jne compare
	inc rcx ; increment the iterator
	jmp loop

compare:
	sub r9b, r8b ; r9b -= r8b
	movsx rax, r9b ; move and get the sign please
	cmp rax, 0 ; compare to 0 to determine -/+ equal
	jg greater
	je end
	jl less

greater:
	mov rax, 1
	jmp end

less:
	mov rax, -1
	jmp end

end:
	mov rsp, rbp
	pop rbp ; epilogue
	ret ; pop rip
