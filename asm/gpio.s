.equ GPIO_CTRL_ADDR, 0x20200000

/* SetGpioFunction: Sets given GPIO pin to given function
 * r0: Pin
 * r1: Function
 */
.globl SetGpioFunction
SetGpioFunction:
	// Check arguments, return if incorrect
	cmp r0, #53
	cmpls r1, #7
	movhi pc, lr

	// Save first argument in r2, load GPIO address
	mov r2, r0
	ldr r0, =GPIO_CTRL_ADDR

	// Set r0 to right control word, r2 to arg1 % 10
	functionLoop$:
		cmp r2, #9
		subhi r2, #10
		addhi r0, #4
		bhi functionLoop$

	// Shift the function by (pinNum % 10) * 3
	add r2, r2, lsl #1
	lsl r1, r2

	// Create an (inverted) mask
	mov r3, #7
	lsl r3, r2
	
	// Save r4 and load the current word into it
	push {r4}
	ldr r4, [r0]

	// Clear the 3 bits corresponding to the pin we are setting
	bic r4, r4, r3
	// ORR the stuff to finish
	orr r1, r1, r4

	// Store and return
	str r1, [r0]
	pop {r4}
	mov pc, lr

/* SetGpio: Sets the given pin on/off
 * r0: The pin
 * r1: Zero for off, nonzero for on
 */
.globl SetGpio
SetGpio:
	pinNum .req r0
	pinVal .req r1
	// Check arguments, return if incorrect
	cmp pinNum, #53
	movhi pc, lr
	
	// Save pinNum to r2, load gpioAddr in r0
	mov r2, pinNum
	.unreq pinNum
	pinNum .req r2
	ldr r0, =GPIO_CTRL_ADDR
	gpioAddr .req r0

	// Determine "bank" (word) for control by (pinNum / 32 (truncated)) * 4 (for offset)
	pinBank .req r3
	lsr pinBank, pinNum, #5
	lsl pinBank, #2
	add gpioAddr, pinBank
	.unreq pinBank

	// Set correct bit
	and pinNum, #31
	setBit .req r3
	mov setBit, #1
	lsl setBit, pinNum
	
	// Save r4 and store the current "bank" in it
	push {r4}
	teq pinVal, #0
	ldreq r4, [gpioAddr, #40]
	ldrne r4, [gpioAddr, #28]

	// OR the set bit with the current word (if it even works dat way lol)
	orr setBit, setBit, r4

	// Store and return
	teq pinVal, #0
	.unreq pinVal
	streq setBit, [gpioAddr, #40]
	strne setBit, [gpioAddr, #28]
	.unreq setBit
	.unreq gpioAddr
	
	pop {r4}
	mov pc, lr


