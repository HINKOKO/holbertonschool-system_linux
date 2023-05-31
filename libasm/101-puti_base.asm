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

	cmp r8, 0
	jge afterdash
	imul r8, -1
	mov r14, 1 ; trick to keep track of negative
	mov rdi, 45 ; '-'
	call asm_putc

afterdash:
	mov rdi, rsi ; asm_strlen written for rdi computation
	call asm_strlen
	mov rbx, rax ; result of asm_strlen => in rbx, will be used as a divisor to convert
	cmp rbx, 1
	jnz first
	mov r10, r8

first:
	test r8, r8 ; check for end of n
	jnz while_number
	movzx rdi, byte [rsi]
	call asm_putc
	mov r14, 1

while_number:
	test rbx, rbx
	jz while_no_base
	xor rdx, rdx
	test r8, r8
	jz next_loop
	mov rax, r8
	div rbx
	mov r8 , rax
	xor rax, rax
	mov al, byte [rsi + rdx]
	push rax
	inc r10
	jmp while_number


while_no_base:


next_loop:
	mov r8, r10

print_loop:
	test r8, r8 ; set a stopper-printer
	jz print_done
	pop rdi

after_pop:
	call asm_putc
	dec r8
	jmp print_loop

print_done:
	cmp r14, 1
	jne end
	inc r10

end:
	mov rax, r10
	pop r14
	pop r12
	pop r10
	pop r8
	mov rsp, rbp
	pop rbp
	ret
