BITS 64
	global	asm_strcmp

asm_strcmp:
	; registers in order rdi, rsi, rdx, rcx, r8, r9
	push rbp
	mov rbp, rsp ; setup
	cmp rdi, 0
	je end
	cmp rsi, 0
	je end
	xor rcx, rcx ; trick xor to initialize counter to 0 fast

loop:
	mov r9b, [rdi + rcx] ; get the first character of 1st string
	mov r8b, [rsi + rcx] ; get the first character of 2nd string
	cmp r9b, 0 ; check for end of string 1
	je compare
	cmp r8b, 0 ; check for end of string 2
	je compare
	cmp r9b, r8b
	jne compare
	inc rcx
	jmp loop

compare:
	sub r9b, r8b ; r9b -= r8b
	movsx rax, r9b ; move and get the sign please
	cmp rax, 0 ; compare to 0
	jg greater
	cmp rax, 0 ; compare to 0
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
	pop rbp
	ret
