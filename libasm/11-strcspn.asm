bits 64

	global asm_strcspn ; export the function
	section .text
	; prototype ==> size_t asm_strcspn(const char *s, const char *reject)
	; The strcspn() computes the length of the initial segment of "s" which consists
	; entirely of bytes NOT in reject (charset become a reject charset huhuha)

asm_strcspn:
	push rbp
	mov rbp, rsp ; A beautiful prologue

	push rcx
	push r8
	push r9 ; save those babies

	xor rax, rax ; clear accumulator
	xor r8, r8
	xor r9, r9

loop_s:
	mov r8b, [rdi + rcx]
	test r8b, r8b
	jz end
	xor rcx, rcx

loop_reject:
	mov r9b, [rsi + rcx]
	test r9b, r9b
	jz end
	cmp r8b, r9b
	jne increment
	inc rcx
	jmp loop_reject

increment:
	inc rax
	jmp loop_s

end:
	pop r9
	pop r8
	pop rcx ; restore the registers

	mov rsp, rbp
	pop rbp
	ret

