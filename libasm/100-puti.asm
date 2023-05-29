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
	mov rbp, rsp ; prologue stack frame
	push r8
	push r9
	push r10
	push rdi ; save the value of n

	xor r8, r8
	xor r9, r9
	xor r10, r10
	movsx r8, edi
	xor rax, rax

	cmp r8, 0 ; compare specific equals 0
	jge positive
	mov r10, 1 ; trick to keep track of negative (count + 1)
	imul r8, -1
	mov rdi, 45 ; '-' character
	call asm_putc

positive:
	test r8, r8
	jnz convert_loop
	mov rdi, 48 ; putting 0
	call asm_putc
	mov r10, 1

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
	mov r8, r9 ; count in r8


print_loop:
	test r8, r8 ; counter reached 0 ?
	jz print_end ;
	pop rdi
	add rdi, 48
	call asm_putc
	dec r8 ; to loop until 0
	jmp print_loop

print_end:
	cmp r10, 0x1
	jne end
	inc r9

end:
	mov rax, r9
	pop r10
	pop r9
	pop r8

	mov rsp, rbp
	pop rbp
	ret
