bits 64

	global asm_strchr ; export the function

	section .text
		; char *asm_strchr(const char *s, int c)
		; returns a pointer to the first occurence of character c in string s
		; => char declared as an 'int c' in proto so strchr can handle not only
		; individual characters but also special values
		; gets implicitly converted to its ASCII code when calling the function

asm_strchr:
; order of registers => rdi, rsi, rdx, rcx, r8, r9
	push rbp ; save the base pointer
	mov rbp, rsp ; set up a new base == Prologue

	mov rsi, [rbp + 8] ; load string address into rsi
	mov cl, [rbp + 12] ; load character to look for

search_loop:
	lodsb ; Load a byte from [RSI] into AL and increment RSI
	cmp al, cl ; compare loaded byte from string with the char
	je c_found ; jump if match
	test al, al ; check if end of string
	jnz search_loop ; if not repeat the loop

	xor rax, rax ; set rax to 0 (not found)
	jmp end

c_found:
	sub rsi, 1 ; decrement RSI to point to the found character
	mov rax, rsi ; Move the pointer to rax

end:
	mov rsp, rbp ; Restore stack pointer
	pop rbp ; Restore base pointer (epilogue)
	ret
