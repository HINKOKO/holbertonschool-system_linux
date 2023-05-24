bits 64

	global asm_strncmp ; exporting the function

	section .text
	; int asm_strncmp(const char *s1, const char *s2, size_t n);
	; the asm_strncmp function compares only the first at most n bytes of s1 and s2

asm_strncmp:

loop:
	cmp rdx, 0 ; register with 'n' parameter, args3
	mov r8b, [rdi] ; move 1 char at a time from s1 r8b => 1 byte
	mov r9b, [rsi] ; move 1 char at a time from s2 r9b => 1 byte
	cmp r8b, r9b ; compare register and jumps accordingly if one "wins"
	jl less
	jg greater
	cmp r8b, 0 ; check if end of string in register r8b
	je equal ; if yes strings equal
	inc rdi
	inc rsi
	dec rdx ; decrement n parameter => we go to next char
	jmp loop ; repeat the loop

less:
	mov eax, -1 ; result negative s1 is less than s2 til n
	ret ; return the value

greater:
	mov eax, 1 ; result positive s1 greater than s2 til n
	ret ; return the value

equal:
	mov eax, 0 ; equality of strings up to n
	ret ; return the value
