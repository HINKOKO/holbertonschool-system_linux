bits 64

	global asm_memcpy

	section .text
	; copycat of the C function 'memcpy'
	; void *asm_memcpy(void *dest, const void *src, size_t n)
	; copies n bytes from memory area src to memory area dest.

asm_memcpy:

	test rdx, rdx ; check if args[3] not NULL
	je end ; if yes its already the end
	mov r8b, byte[rsi] ;
	mov byte [rdi], r8b
	inc rsi
	inc rdi
	dec rdx
	jmp asm_memcpy

end:
	ret
