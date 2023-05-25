bits 64

	global asm_strstr ; export the function

	section .text
	; asm_strstr is copycat of C function strstr
	; locates a subtring 'needle' in the 'haystack' of a mega huge (or not) string


asm_strstr:
	push rbp
	mov rbp, rsp ; setup stack frame

	push rcx ; iterator 'i' for str1
	; more "logical" to keep rcx counter for str1 => nope(?)
	push rbx ; iterator 'j' for str2
	push rdx ; register to store index finding
	push r8
	push r9 ; those two buddies as tmp storage for str1 & str2

	xor rax, rax
	xor rcx, rcx ; clear those register before use (segfault otherwise for these 2)
	xor rbx, rbx
	xor rdx, rdx
	xor r8, r8
	xor r9, r9

strstr_loop:
	mov rdx, rcx ; save the idx if match in next step
	xor rbx, rbx ; clear 'j' iterator 2, start again at needlestring[0]

strstr_match_loop:
	mov r8b, [rdi + rcx] ; rdi => 1st arg => 1st string + iterate to it
	mov r9b, [rsi + rbx] ; rsi => 2nd arg => idem...
	test r9b, r9b ; trick to check if str2 is over ?
	jz matching_idx ; if yes, jump to mathcing_idx
	cmp r8b, r9b ; if no compare chars from str1 & str2
	jne break ; if not, jump to break (to move iterator 1 among other things)
	inc rcx ;
	inc rbx ; if all of this pass increment and repeat
	jmp strstr_match_loop ; Repeat the loop

matching_idx:
	mov rax, rdi
	add rax, rdx

break:
	mov r8b, [rdi + rcx]
	test r8b, r8b ; is it end of string 1 ?
	jz end ; if yes, smells like exiting
	inc rcx ; if not increment again iterator and let's go
	jmp strstr_loop ; jump to strstr_loop

end:
	; restore our working registers
	pop r9
	pop r8
	pop rdx
	pop rbx
	pop rcx

	mov rsp, rbp
	pop rbp
	ret

