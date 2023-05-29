bits 64

	global asm_strcspn ; export the function
	section .text
	; prototype ==> size_t asm_strcspn(const char *s, const char *reject)
	; The strcspn() computes the length of the initial segment of "s" which consists
	; entirely of bytes NOT in reject (charset become a reject charset huhuha)

asm_strcspn:
	push rbp
	mov rbp, rsp ; A beautiful prologue

	xor rax, rax ; clear accumulator
	xor rcx, rcx

loop:
	mov r8b, [rdi + rcx]
	mov r9b, [rsi + rcx]
	test r8b, r8b
	jz end
	test r9b, r9b
	jz bingo
	cmp r8b, r9b
	je end
	inc rcx
	jmp loop

bingo:
	inc rax
	jmp loop

end:
	mov rsp, rbp
	pop rbp
	ret

