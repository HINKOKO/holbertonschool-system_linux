bits 64

	global asm_strcasecmp ; expor the function

	section .text
	; copycat of function strcasecmp
	; int asm_strcasecmp(const char *s1, const char *s2);
	; what the HELL IS THAT FUNCTION ?
	; ******* DRAFT THOUGHTS ********
	; It compares 2 strings in a case-INSENSITIVE Manner
	; Let's go => char in str1 is equal to str2 ? don't give a damn about case
	; move on to next char
	; Now imagine it founds different characters ==>
	; if str1 char is 'greater' than str2 char => positive value (based on ASCII values)
	; if str1 char is 'less' than str2 char => negative
	; finally if one string ends before a difference is found => the length of strings is used to compute the result
	; but testing this behavior gives weird result, try it out with a homemade main using strcasecmp ;)
	; Thanks
	; ******* END OF DRAFT THOUGHTS ********
	; *** Thanks IBM Docs ***
	; => strcasecmp() function compares str1 & str2 without sensivity case
	; All alphabetics characters are converted to lower before comparison

asm_strcasecmp:
	push rbp
	mov rbp, rsp ; that's a good prologue
	push rcx
	push r8
	push r9

	xor rcx, rcx ; clean up counter
	xor r8, r8
	xor r9, r9 ; clear the temp purposed registers for greeting strings

mainloop:
	mov r8b, [rdi + rcx] ; load one byte of str1
	mov r9b, [rsi + rcx] ; load one byte of str2
	cmp r8b, 0x41
	jl second_string
	cmp r8b, 0x5A
	jg second_string
	add r8b, 0x20

second_string:
	cmp r9b, 0x41
	jl compare
	cmp r9b, 0x5A
	jg compare
	add r9b, 0x20

compare:
	movzx eax, r8b
	sub eax, r9d
	test eax, eax
	jnz end
	test r8b, r8b
	jz end
	inc rcx
	jmp mainloop

end:
	pop r9
	pop r8
	pop rcx

	mov rbp, rsp
	pop rbp
	ret
