BITS 64

	global print_alphabet ; Export the function
	
	section .text

	; void print_alphabet(void)
	; prints alphabet in lowercase

print_alphabet:
	push rbp ; save base pointer
	mov rbp, rsp ; set_up stack fram

	push rsi
	push rax
	push rdi
	push rdx ; push the registers to save if they were in use

	add rsp, -1 ; Increase (toward low addresses) 1 byte (1 char)
	mov byte [rsp], 97 ; ASCII value of 'a' stored in the place we reserved

	; Setup the 'write' syscall
	mov rax, 1 ; syscall 1 == write
	mov rdx, 1 ; Data register, record the 1 byte we write
	mov rbi, 1 ; Destination Index Register, used destination stream ops (1 == stdout)
	mov rsi, rsp ; Address of the stack 
	; RSI used as a pointer to a source in stream operations

loop_alphabet:
	syscall ; trigger the syscall
	inc byte [rsp] ; Increment stack pointer
	cmp byte [rsp], 122 ; compare value to 122 ASCII 'z'
	jle loop_alphabet ; if less than 122 repeat loop (Jump LEss)

end:
	; 'end' not necessary but code way more understandable
	; handles restoration of registers and epilogue for stack frame
	pop rdx
	pop rdi
	pop rax
	pop rsi ; restore our register backwards

	mov rsp, rbp ; restore previous stack frame
	pop rbp
	ret ; return (pop 'rip' => RIP register Instruction Pointer, Current Instruction pointer)



