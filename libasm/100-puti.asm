bits 64

global asm_puti ; export the function
extern asm_putc ; import the asm_putc from task 6

section .text

; size_t asm_puti(int n) => return the total number of bytes written on stdout
; n => integer to be printed
; asm_puti(98) => 2
; asm_puti(-1024) => 5

asm_puti:
	push rbp
	mov rbp, rsp
	push r8
	push r9
	push r10

	xor r8, r8
	xor r9, r9
	xor r10, r10
	movsx r8, rdi
	xor rax, rax

	cmp r8, 0
	jge positive
	imul r8, -1
	mov rdi, 45
	call asm_putc

positive:
	test r8, r8
	jnz convert_loop
	mov rdi, 48
	call

convert_loop:
	xor rdx, rdx
	test r8, r8 ; end of 'n' number ? go to next
	jz next
	mov rax, r8
	mov rbx, 10 ; base 10 to divide
	div rbx ; rax /= rbx

	mov r8, rax ; quotient in rax
	push rdx ; remainder in rdx

	inc r9 ; count the bytes written
	jmp convert_loop

next:

print_loop:
	test r8, r8
	jz whatever ; ???

end:
	pop r10
	pop r9
	pop r8

	mov rsp, rbp
	pop rbp
	ret
