bits 64

	global asm_strncasecmp ; expor the function

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

asm_strncasecmp:
	push rbp
	mov rbp, rsp ; that's a good prologue

	push rcx
	push r8
	push r9

	xor rcx, rcx ; clean up counter
	xor r8, r8
	xor r9, r9 ; clear the temp purposed registers for holding strings

mainloop:
	mov r8b, [rdi + rcx] ; load one byte of str1
	mov r9b, [rsi + rcx] ; load one byte of str2
	cmp r8b, 0x41 ; compare with A value hex (man 7 ascii)
	jl second_string ; if less jump to second string handling
	cmp r8b, 0x5A ; compare with Z value hex
	jg second_string ; if greater jump to second string handling
	add r8b, 0x20 ; if 0x41 <= r8b <= 0x5A |then => +=32 to convert

second_string:
	cmp r9b, 0x41 ; same stuff as string 1
	jl compare ; if not upper too, lets make a contest between !
	cmp r9b, 0x5A ; same stuff as string 1
	jg compare ; if not upper too, lets make a contest !
	add r9b, 0x20 ; if upper += 32 to convert

compare:
	test rdx, rdx ; check if n parameter is null
	jz end
	dec rdx ; n-- as we go
	movzx eax, r8b ; movzx to 'zero extend' when we come from lower to bigger register to keep safe value
	sub eax, r9d ; r9'd' to 'match' the 32 bits of eax
	test eax, eax ; if not 0 jump to end
	jnz end
	test r8b, r8b ; did we reach end of string1
	jz end ; if yes go to end
	inc rcx ; increment iterator
	jmp mainloop ; back to mainloop to repeat

equal:
	mov rsp, rbp
	pop rbp
	mov eax, 0
	ret

end:
	pop r9
	pop r8
	pop rcx ; restore the registers we pushed

	mov rbp, rsp
	pop rbp
	ret
