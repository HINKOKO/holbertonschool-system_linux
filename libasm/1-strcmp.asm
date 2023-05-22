BITS 64
	global	asm_strcmp

asm_strcmp:
	; registers in order rdi, rsi, rdx, rcx, r8, r9
loop:
	mov r8b, byte [rdi]
	mov r9b, byte [rsi]
	inc rdi
	inc rsi
	cmp r8b, r9b
	jl less
	jg greater
	cmp r8b, 0
	je end
	jmp loop

greater:
	mov eax, 1
	ret
less:
	mov eax, -1
end:
	mov eax, 0
	ret
