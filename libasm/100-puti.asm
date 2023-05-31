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
	push r10
	push r12
	push rdi ; save the value of n

	xor r8, r8
	xor r10, r10
	xor r12, r12 ; clear registers for proper start
	movsx r8, edi
	xor rax, rax ; clear accumulator

	cmp r8, 0 ; compare n value to 0
	jge positive ; jump to positive if greater or equal
	mov r12, 1 ; trick to keep track of negative a negative n (like setting a fake leftmost bit to 1)
	imul r8, -1 ; convert to positive temporary
	mov rdi, 45 ; character '-'
	call asm_putc ; print it

positive:
	test r8, r8 ; check end of n
	jnz convert_loop ; if not 0 jump to convert loop
	mov rdi, 48 ; putting 0
	call asm_putc
	mov r12, 1

convert_loop:
	xor rdx, rdx
	test r8, r8 ; end of 'n' number ? go to next
	jz next
	mov rax, r8
	mov rbx, 10 ; base 10 to divide
	div rbx ; rax /= rbx

	mov r8, rax ; quotient in rax
	push rdx ; remainder in rdx => push to the stack

	inc r10 ; count the bytes written
	jmp convert_loop

next:
	mov r8, r10 ; count in r8


print_loop:
	test r8, r8 ; counter reached 0 ?
	jz print_end ;
	pop rdi ; pop the remainders, which are on stack, to rdi
	add rdi, 48
	call asm_putc ; putc works on rdi
	dec r8 ; to loop until 0
	jmp print_loop

print_end:
	cmp r12, 0x1
	jne end
	inc r10

end:
	mov rax, r10 ; putt in rax the bytes written
	pop r12
	pop r10
	pop r8 ; restore registers

	mov rsp, rbp
	pop rbp ; epilogue
	ret ; pop rip
