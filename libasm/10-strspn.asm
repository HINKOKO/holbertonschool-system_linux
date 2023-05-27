bits 64

	global asm_strspn ; export the function
	section .text

	; size_t strspn(const char *s, const char *accept)
	; calcultates the length (bytes) of initial segment of "s" which consists entirely
	; of bytes in "accept"
	; ==> S1 = "Holberton"
	; ==> S2 = "holberton"
	; ==> ACCEPT1 = "abcdefghijklmnopqrstuvwxyz" (lowercase acceptance)
	; ==> ACCEPT2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (Uppercutcase acceptance)
	; strspn(S1, A2) = ......... 1 !
	; strspn (S2, A1) = ........ 9 !

asm_strspn:
	push rbp
	mov rbp, rsp

	push rcx
	push r8
	push r9 ; push needed register if were in use

	xor rax, rax ; here use as a the iterator of string *s
	xor r8, r8
	xor r9, r9 ; initialize those registers to 0 to hold bytes of strings

loopin_s:
	mov r8b, [rdi + rax] ; load one byte of s
	test r8b, r8b ; test end of string s
	jz end
	xor rcx, rcx ; clear charset iterator => start again at begin

loopin_charset:
	mov r9b, [rsi + rcx] ; load one byte of charset accept
	test r9b, r9b ; check for end of charset
	jz end
	cmp r8b, r9b ; compare chars
	je increment
	inc rcx
	jmp loopin_charset

increment:
	inc rax
	jmp loopin_s

end:
	pop r9
	pop r8
	pop rcx

	mov rsp, rbp
	pop rbp
	ret
