.section .init
.globl _start
_start:
	b main

.section .text
.globl main
main:
	mov sp, #0x8000
	
	mov r0, #1024
	mov r1, #768
	mov r2, #16
	bl InitialiseFrameBuffer

	teq r0, #0
	bne noError$

	mov r0, #47
	mov r1, #1
	bl SetGpioFunction
	mov r0, #47
	mov r1, #0
	bl SetGpio

	error$:
		b error$

	noError$:
		bl SetGraphicsAddress 
		
		ldr r0, =format
		bl CharCount

		mov r1, r0
		ldr r0, =format
		ldr r2, =dest
		ldr r3, =-32
		bl FormatString

		
		ldr r0, =dest
		mov r1, #0
		mov r2, #0
		bl DrawStringz

		lewp$:
			b lewp$

		.section .data
		format:
		.asciz "This is a number: %d"
		formatEnd:

		.section .bss
		dest:
			.space 100
