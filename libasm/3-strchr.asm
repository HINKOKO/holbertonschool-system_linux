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
	xor rax, rax ; quick trick to effitcient clear rax to 0
	; using rax for arithmetics (iterator)

loop:
	cmp BYTE [rdi + rax], 0 ; is the end of string already ?
	jz end ; if equals 0 jump to end


	cmp BYTE [rdi + rax], sil ; compare current char with targeted char
	jz found ; if equals 0 jump to found

	inc rax ; increment iterator
	jmp loop ; Repeat loop

found:
	lea rax, [rdi + rax] ; load effective address of char found in rax
	ret

end:
	xor rax, rax ; no found clear rax
	ret ; return
