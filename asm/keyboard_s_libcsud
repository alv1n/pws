.section .data
.align 2
KeyboardAddress:
	.int 0

KeyboardOldDown:
	.rept 6
	.hword 0
	.endr

.section .text
.globl KeyboardUpdate
KeyboardUpdate:
	push {r4 - r6, lr}

	ldr r0, =KeyboardAddress
	ldr r4, [r0]

	teq r4, #0
	bne haveKeyboard$
	
	// If KeyboardPoll fails
	KeyboardPollErr$:
	bl UsbCheckForChange
	
	// Check if there are any keyboards connected (and store zero in KeyboardAddress if there aren't any)
	bl KeyboardCount
	teq r0, #0
	ldreq r1, =KeyboardAddress
	streq r0, [r1]
	beq return$

	// Get the keyboard address and store it
	mov r0, #0
	bl KeyboardGetAddress
	ldr r1, =KeyboardAddress
	str r0, [r1]
	
	// Check if KeyboardGetAddress was succesful
	teq r0, #0
	// Maybe return an error code?
	beq return$

	// If we did not have a keyboard yet, we have it now	
	mov r4, r0
		
	haveKeyboard$:
	mov r5, #0
	ldr r6, =KeyboardOldDown	
	GetKeyDownLoop$:
		// Get a key that's down
		mov r0, r4
		mov r1, r5
		bl KeyboardGetKeyDown
		
		// store it safely, cuz it returns 0 when asking for too many
		strh r0, [r6]
		
		add r6, #2
		add r5, #1
		cmp r5, #6
		blo GetKeyDownLoop$
	
	// ?
	mov r0, r4
	bl KeyboardPoll
	teq r0, #0
	bne KeyboardPollErr$

	return$:
	pop {r4 - r6, pc}


/* KeyWasDown: Checks if a given scancode 'was down'
 * r0: scancode
 * returns nonzero if key was down, zero if not
 */
.globl KeyWasDown
KeyWasDown:
	ldr r2, =KeyboardOldDown
	mov r3, #0

	keyWasDownLoop$:
		ldr r1, [r2, r3, lsl #1]
		teq r0, r1
		moveq r0, #1
		moveq pc, lr

		add r3, #1
		cmp r3, #6
		blo keyWasDownLoop$
	
	mov r0, #0
	mov pc, lr

.section .data
// Lookup table for KeyboardGetChar
.align 3
KeysNormal:
	.byte 0x0, 0x0, 0x0, 0x0, 'a', 'b', 'c', 'd'
	.byte 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'
	.byte 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'
	.byte 'u', 'v', 'w', 'x', 'y', 'z', '1', '2'
	.byte '3', '4', '5', '6', '7', '8', '9', '0'
	.byte '\n', 0x0, '\b', '\t', ' ', '-', '=', '['
	.byte ']', '\\', '#', ';', '\'', '`', ',', '.'
	.byte '/', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+'
	.byte '\n', '1', '2', '3', '4', '5', '6', '7'
	.byte '8', '9', '0', '.', '\\', 0x0, 0x0, '='

.align 3
KeysShift:
	.byte 0x0, 0x0, 0x0, 0x0, 'A', 'B', 'C', 'D'
	.byte 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'
	.byte 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'
	.byte 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"'
	.byte '£', '$', '%', '^', '&', '*', '(', ')'
	.byte '\n', 0x0, '\b', '\t', ' ', '_', '+', '{'
	.byte '}', '|', '~', ':', '@', '¬', '<', '>'
	.byte '?', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	.byte 0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+'
	.byte '\n', '1', '2', '3', '4', '5', '6', '7'
	.byte '8', '9', '0', '.', '|', 0x0, 0x0, '='

.section .text
/* KeyboardGetChar: returns the character corresponding to the last key pressed
 * r0: key
 */
.globl KeyboardGetChar
KeyboardGetChar:
	// Check if KeyboardAddress is 0. If so, return 0
	ldr r1, =KeyboardAddress
	ldr r0, [r1]
	teq r0, #0
	bne returnChar$

	push {r4 - r6, lr}

	mov r4, r0
	mov r5, #0
	getCharLoop$:
		mov r0, r4
		mov r1, r5
		bl KeyboardGetKeyDown
		mov r6, r0

		// If key (scancode) is 0, exit loop
		teq r6, #0
		beq returnChar$

		// Call KeyWasDown. If it was, go to next key. (r0 already contains scancode)
		bl KeyWasDown
		teq r0, #0
		bne continueLoop$

		// If the scan code is more that 103, go to the next key
		cmp r6, #103
		bhi continueLoop$
		
		// Call KeyboardGetModifiers
		mov r0, r4
		bl KeyboardGetModifiers

		// If shift is held, load the address of KeysShift.
		// Otherwise load KeysNormal.
		tst r0, #0x22
		ldrne r1, =KeysShift
		ldreq r1, =KeysNormal

		// Read the ASCII value from the table
		ldrb r0, [r1, r6]

		// If it is 0, go to the next key, otherwise return this ASCII code and exit
		teq r0, #0
		bne returnChar$
		
		continueLoop$:
		add r5, #1
		cmp r5, #6
		blo getCharLoop$

	returnChar$:
	pop {r4 - r6, pc}
	
	
		
		
		
		

	
