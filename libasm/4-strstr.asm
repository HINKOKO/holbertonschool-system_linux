bits 64

	global asm_strstr ; export the function

	section .text
	; asm_strstr is copycat of C function strstr
	; locates a subtring 'needle' in the 'haystack' of a mega huge (or not) string
	; strstr => finds the first occurence of 'needle' in 'haystack' ('\0' not compared)
	; returns a pointer to begin of located substring , NULL not found


asm_strstr:
	push rbp
	mov rbp, rsp ; classic prologue
	cmp rdi, 0 ; check if str1 is NULL
	je error ; if yes jump to handle error
	cmp rsi, 0 ; check if str2 is NULL
	je error ; if yes jump to handle error
	jmp boot ; jump to boot

boot:
	mov r8b, [rdi] ; set/reset r8b with str[i] at updated position to continue comparison
	xor rcx, rcx ; clear the counter
	jmp while ; jump to the 'core' while loop

reboot_comp:
	cmp r8b, 0 ; check if str1[i] != '\0'
	je no_equal ; if yes jump to no equal (str2 not finished but str1 yes => problem needle bigger than haystack)
	inc rdi ; str1[i++] move the iterator one step
	jmp boot

while:
	mov r8b, [rdi + rcx] ; temp r9b now hosting str1[i]
	mov r9b, [rsi + rcx] ; temp r8b hosting str2[i]
	cmp r9b, 0 ; did we reach end of needle string (str2) ?
	; step is strange but we will never be here if str2 is NULL
	; just to ensure if needle is one char (that's a needle really)
	; and find boom occurs
	je strings_equal ; if yes jump to string_equals
	cmp r8b, r9b ; compare str1[i] & str2[i]
	jne reboot_comp ; if no jump to init_val
	inc rcx ; move our counter += 1
	jmp while ; Repeat the loop

strings_equal:
	mov rax, rdi ; store in rax the index str1[i]
	jmp end ; jump to end

no_equal:
	xor rax, rax ; clear up the rax register => return 0
	jmp end

error:
	xor rax, rax ; clear up register => return 0
	jmp end

end:
	mov rsp, rbp
	pop rbp ; classic epilogue
	ret ; pop rip => return ptr or 0

