/* DivideU32: Divides an unsigned number. By another unsigned number. Wow.
 * r0: unsigned dividend
 * r1: unsigend divisor
 * returns the quotient and remainder in r0 and r1 respectively
 */
.globl DivideU32
DivideU32:
	result .req r0
	remainder .req r1
	shift .req r2
	current .req r3

	clz shift, r1
	clz r3, r0
	// if r0 < r1, the correct return value is already in r0 and r1, so return
	subs shift, r3
	lsl current, r1, shift
	mov remainder, r0
	mov result, #0
	blt divideU32Return$

	divideU32Loop$:
		cmp remainder, current
		blt divideU32LoopContinue$
		
		add result, result, #1

		// shortcut: if the remainder minus 'current' is exactly zero, just shift the result so far by 'shift' and return
		// otherwise, just continue the loop
		subs remainder, current
		lsleq result, shift
		beq divideU32Return$
	divideU32LoopContinue$:
		subs shift, #1
		lsrge current, #1
		lslge result, #1
		bge divideU32Loop$

	divideU32Return$:
	mov pc, lr
	
	.unreq current
	.unreq result
	.unreq remainder
	.unreq shift


