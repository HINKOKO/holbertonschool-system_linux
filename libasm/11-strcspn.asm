bits 64

	global asm_strcspn ; export the function
	section .text
	; prototype ==> size_t asm_strcspn(const char *s, const char *reject)
	; The strcspn() calculates and returns the length of the initial segment of string 's'
	; that does not contain any character from the character set 'reject'
	; In Other words ==> searches for the first occurence of any character from 'reject' in 's'
	; and returns the position of that character (that's why example 3 give that result)
	; strcspn("HOLBERTON", "abcdefghijklmnopqrstuvwxyz") => 9
	; strcspn("HOLBERTON", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") => 0
	; strcspn("HahgjldoHaHaHa", "abcdefghijklmnopqrstuvwxyz") => 1 (a at index 1)
	; strcspn("BAKANga", "abcdefghijklmnopqrstuvwxyz") => 5 (g at index 5)


asm_strcspn:
	push rbp
	mov rbp, rsp ; A beautiful prologue

	xor rax, rax ; clear accumulator
	mov rdx, rsi ; keep safe the value of rsi, so we can work with rsi in a loop

loop:
	movzx ebx, byte [rdi] ; load one char from 's'
	cmp bl, 0x0 ; check if s = '\0'
	jz end ; if yeah it's over
	cmp byte [rsi], 0x0 ; check end of charset 'reject'
	jz segment_growth ; if yes jump to bingo
	cmp bl, byte [rsi] ; compare chars
	je end ; if equal the end
	inc rsi ; move on to next char in 'reject'
	jmp loop ; repeat the loop

segment_growth:
	inc rax ; adding one to the segment length in 's'
	inc rdi ; move on to next char in 's'
	mov rsi, rdx ; restore-reset the value of 'reject', start again
	jmp loop ; go back to loop

end:
	mov rsp, rbp
	pop rbp
	ret

