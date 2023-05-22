bits 64

section .text
global asm_strncmp ; exporting the function

asm_strncmp:
	push rbp ; prologue
	mov rbp, rsp
	push rbx
	push rcx
	push r11
	push r12
	push r13

	mov rbx, rdi ; save 1st arg in rbx register
	mov rcx, rsi ; save 2nd arg in rcx register
	mov r11, rdx ; save 3rd arg in r11 register
	mov r12, 0 ; set a counter to 0

count_loop:
	inc r12 ; increment counter
	cmp r12, r11 ; check if count greater than n bytes parameter passed to strncmp function
	jg correction ; if yes go to correction and decrease back count
	mov r13b, byte [rcx + r12 - 1]
	cmp r13b, byte 0x00 ; check if not a null char in arg1
	je next_loop ; if yeah get the hell out and jump next loop
	cmp r13b, byte [rbx + r12 - 1] ; check if not a null char in arg2
	je next_loop
	cmp r13b, byte [rcx + r12 - 1] ; compare char from arg1 & arg2
	je count_loop ; Repeat the loop

correction:
	dec r12;
	jmp next_loop

next_loop:
	mov rax, 0 ; init return value 0
	push qword [rbx + r12 - 1] ; put the last char arg1 compared onto stack
	push qword [rcx + r12 - 1] ; put the last char arg2 compared onto stack
	mov rbx, 0 ; set register to 0
	mov rcx, 0 ; set register to 0
	mov bl, byte [rsp + 8] ; move the last char from arg1 in a variable
	mov cl, byte [rsp] ; move the last char from arg2 in a variable
	cmp rbx, rcx ; compare the two previous buddies
	je equal
	jl less
	jg greater


equal:
	mov rax, 0 ; set return val to 0
	jmp end ; jump to end of program

less:
	mov rax, -1 ; set return value to -1
	jmp end ; jump to end

greater:
	mov rax, 1 ; set return value to 1
	jmp end ; jump to end

end:
	pop rdx
	pop rcx
	pop r13
	pop r12
	pop r11
	pop rcx
	pop rbx ; restore register backwards
	mov rsp, rbp
	pop rbp ; epilogue of stack frame
	ret

