bits 64

global asm_puti ; export the function
extern asm_putc ; import the asm_putc from task 6

section .text

; size_t asm_puti(int n) => return the total number of bytes written on stdout
; n => integer to be printed
; asm_puti(98) => 2
; asm_puti(-1024) => 5

asm_puti:
	mov eax, edi ; function arg 'n'
	mov ecx, 0xa ; base 10*

	push rcx
	mov rsi, rsp
	sub rsp, 16

.toascii_digit: ; do{
	xor edx, edx
	div ecx ; edx = remainder = low digit eax/=10
	add edx, '0'
	dec rsi
	mov [rsi], dl
	test eax, eax ; } while (x)
	jnz .toascii_digit

;;; rsi points to the fist digit
	mov eax, 1 ; write syscall
	mov edi, 1 ; fd = STDOUT_FILENO
	lea edx, [rsp + 16 + 1]
	sub edx, esi
	syscall

	add rsp, 24

	ret
