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
	mov rbp, rsp ; set up new stack pointer

loop:
	mov al, [rdi] ; load 1 byte of string (1 char) in r8b
	cmp al, sil ; compare with the pattern to find (sil => baby 8 bits of rsi)
	je found ; if equal jump to fond
	test al, al ; test for null terminator
	jz null ; if yes jump to null
	inc rdi ; increment string pointer
	jmp loop ; Repeat the loop

found:
	mov rax, rdi ; Move the adress of matching char to rax

null:
	xor rax, rax ; return NULL to indicate not found, as 'man strchr'
	jmp end ; jump to the end

end:
	mov rsp, rbp ; restore stack pointer
	pop rbp ; restore base pointer
	ret ; return
