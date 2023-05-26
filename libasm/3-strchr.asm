bits 64

	global asm_strchr ; export the function

	section .text
		; char *asm_strchr(const char *s, int c)
		; returns a pointer to the first occurence of character c in string s
		; => char declared as an 'int c' in proto so strchr can handle not only
		; individual characters but also special values
		; gets implicitly converted to its ASCII code when calling the function

; register order => rdi, rsi, rdx, rcx, r8, r9
; sil => 8 bits register of rsi => source index register, used as a pointer
; to a source in stream ops

asm_strchr:
	push rbp ; save base pointer
	mov rbp, rsp ; set_up new stack pointer

loop:
	mov r8b, byte [rdi] ; load 1 byte (1 char) of string (rdi) in al (8 bits baby of rax)
	cmp r8b, sil ; compare with pattern (sil 8bits of rsi (arg2))
	jz found ; if 0 jump to found
	cmp byte [rdi], 0 ; is this end of string yet ?
	jz end ; if yes jump to end
	inc rdi ; increment pointer in string str1[i++]
	jmp loop ; repeat the loop

found:
	mov rax, rdi ; move address of char found in rax
end:
	mov rsp, rbp ; restore stack pointer
	pop rbp ; restore base pointer
	ret ; return, pop rip
