BITS 32 

section .text
	global add_me

add_me:
	; Function prologue
	push ebp ; preserve previous base pointer
	; calling code may have been using 'RBP' for its own purpose
	; preserve and be able to call it later
	mov ebp, esp ; establish new base pointer

	; args accessed related to ebp
	mov eax, [ebp + 8] ; get first
	mov ebx, [ebp + 12] ; get second

	add eax, ebx ; perfomr addition

	; clean up the stack, EPILOGUE !
	mov esp, ebp
	pop ebp

	; return result
	ret
