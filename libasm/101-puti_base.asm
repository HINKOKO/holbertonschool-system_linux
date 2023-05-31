bits 64

global asm_puti_base ; export the function
extern asm_strlen ; import asm_strlen function
extern asm_putc ; import asm_putc function

section .text

; Prototype => size_t asm_puti_base(int n, const char *base)
; prints a signed integer on a given base on stdout


asm_puti_base:
	push rbp
	mov rbp, rsp ; prologue
	push r8
	push r10
	push r12
	push r14

	xor r8, r8
	xor r10, r10
	xor r12, r12
	xor r14, r14
	movsx r8, edi
	xor rax, rax

	cmp r8, 0 ; compare n to 0
	jge positive ; if greater than 0 jump to positive
	imul r8, -1 ; signed multi on r8
	mov r14, 1 ; trick to keep track of original negative 'n'
	mov rdi, 45 ; dash character in rdi
	call asm_putc ; putchar the dash

positive:
	mov rdi, rsi ; asm_strlen written for rdi computation, put the 'base' in rdi
	call asm_strlen ; computes length of 'base' to determine the base
	mov rbx, rax ; result of asm_strlen => in rbx, will be used as a divisor to convert
	cmp rbx, 1 ; compare to 1
	jnz first ; if cmp != jump to first
	mov r10, r8 ; keep a record of n

first:
	test r8, r8 ; check for end of n
	jnz while_number ; if n not finished jump to while number
	movzx rdi, byte [rsi] ;
	call asm_putc
	mov r14, 1

while_number:
	test rbx, rbx ; test if divisor is null/no base specified
	jz while_no_base ; jump to default behavior
	xor rdx, rdx ; clear the remainder register, division coming soon
	test r8, r8 ; set up a stopper when nothing more to divide
	jz next_loop ; jump to next_loop
	mov rax, r8
	div rbx
	mov r8 , rax ; quotient in rax moved back to r8
	xor rax, rax ; now clear rax
	mov al, byte [rsi + rdx] ; move the remainder to al
	push rax ; save to stack
	inc r10 ; increment bytes written
	jmp while_number ; repeat

while_no_base:
	xor rdx, rdx ; clear remainder place
	test r8, r8
	jz next_loop
	mov rax, r8 ; same mechanics as previous while_number label
	mov rbx, 10 ; default behavior base 10
	div rbx
	mov r8, rax ; update r8
	xor rax, rax ; clear rax
	mov rax, rdx ; remainder to accu
	add rax, 48 ; trick ASCII conversion
	push rax ; save value stack
	inc r10 ; increment bytes written
	jmp while_no_base ; repeat the loop

next_loop:
	mov r8, r10 ; restore the 'n'

print_loop:
	test r8, r8 ; set a stopper-printer
	jz print_done
	pop rdi ; pop the 'stacked values' of remainders

after_pop:
	call asm_putc ; prints char
	dec r8 ; n-- until 0
	jmp print_loop ; repeat process

print_done:
	cmp r14, 1 ; check if 'n' was originally negative ?
	jne end ; if 'n' was sweet positive jump to the end !
	inc r10 ; if no, add one byte for the dash (-)

end:
	mov rax, r10 ; move in rax the bytes written
	pop r14
	pop r12
	pop r10
	pop r8 ; restore the registers
	mov rsp, rbp
	pop rbp ; stack frame epilogue
	ret ; pop rip
