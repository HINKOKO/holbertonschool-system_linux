BITS 64

	global swap ; export the function

	section .text

	; void swap(int *a, int *b)
	; swap the values a and b

swap:
	; function prologue, set up stack fram
	push rbp
	mov rbp, rsp

	; cant swap between registers, use the stack location as temporary garage
	; int is 4 bytes == 32 bits so go for 'dword'
	; registerd r_d == 32 bits
	mov r8d, dword [rdi] ; save int argv[1] (RDI) to register 32 bits // why not STACK ??
	mov r9d, dword [rsi] ; save int argv[2] (RSI) to another register 32 bits // WHy not STACK ??
 
	mov dword [rdi] , r9d ; 
	mov dword [rsi] , r8d ; 

	; function epilogues
	mov rsp, rbp
	pop rbp
	ret


