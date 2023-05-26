bits 64

	global asm_memcpy

	section .text
	; copycat of the C function 'memcpy'
	; void *asm_memcpy(void *dest, const void *src, size_t n)
	; copies n bytes from memory area src to memory area dest.

asm_memcpy:
	test rdx, rdx ; check if 3rd parameter of memcpy is Null
	mov r8b, [rsi] ; source aera => 2nd args => rsi
	mov [rdi] , r8b ; move in dest aera => 1st arg => rdi
	inc rsi ; move in source[i++]
	inc rdi ; move in dest area[i++]
	dec rdx ; n--
	jmp asm_memcpy
end:
	ret
