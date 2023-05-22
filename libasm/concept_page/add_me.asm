BITS 64

	global add_me ; export the function

	section .text

	; int add_me(int a, int b)
	; adds two integers

add_me:

	; the 6 first integer/pointer params stored in order rdi, rsi, rdx, rcx, r8 & r9
	; First integer parameter (EDI) // 'e' used because 32 bits asked
	mov eax, edi
	; Second integer parameter added to eax which holds 1st param edi (+ ESI)
	add eax, esi
	; return
	ret

