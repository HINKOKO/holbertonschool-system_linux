bits 64

global asm_strpbrk ; export the function

section .text
; char *strpbrk(const char *s, const char *accept)
; search a string for any of a set of bytes
; the strpbrk() scans the string 's' and returns a pointer to the first occurence
; of any character from the set 'accept'
; if no match => returns null pointer

asm_strpbrk:
	push rbp
	mov rbp, rsp ; set_up => prologue

	xor rax, rax ; clear accumulator proper basis
	mov rbx, rsi ; save the charset 'accept' for preservation between loops

loop:
	movzx edx, byte [rdi] ; load one char from string 's'
	cmp dl, 0x0 ; check if end of string 's'
	je end ; if yeah go to end
	cmp byte [rsi], 0x0 ; check if end of charset 'accept'
	je next ; if yes go to 'next' label to handle next comparison
	cmp dl, byte [rsi] ; compare chars from 's' and 'accept'
	je found ; if equals, let's jump to found
	inc rsi ; accept[i++]
	jmp loop ; repeat the loop

next:
	inc rdi ; move string 's' (s[i++])
	mov rsi, rbx ; 'reset' the charset 'accept'
	jmp loop ; go back to loop

found:
	mov rax, rdi ; move the index of s[i] found to rax register

end:
	mov rsp, rbp
	pop rbp ; this is epilogue bye-bye old stack frame
	ret ; pop rip



