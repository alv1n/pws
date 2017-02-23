.section .data
.align 1
foreColour:
	.hword 0xFFFF

.align 2
graphicsAddress:
	.int 0

.section .text
/* SetForeColour: Set the colour used to draw
 * r0: high colour value
 * no return value
 */
.globl SetForeColour
SetForeColour:
	cmp r0, #0x10000
	movhs pc, lr
	ldr r1, =foreColour
	strh r0, [r1]
	mov pc, lr

/* SetGraphicsAddress: Sets the address to the framebuffer used by drawing function.
 * r0: address of the framebuffer
 * no return value
 */
.globl SetGraphicsAddress
SetGraphicsAddress:
	ldr r1, =graphicsAddress
	str r0, [r1]
	mov pc, lr

/* SetPixel: Sets a pixel to 'forecolour'
 * r0: x coordinate of the pixel
 * r1: y coordinate of the pixel
 */
.globl DrawPixel
DrawPixel:
	// load address of fbinfo
	ldr r2, =graphicsAddress
	ldr r2, [r2]

	// load height, and compare with y coordinate
	ldr r3, [r2, #4]
	cmp r1, r3
	movhs pc, lr

	// load width, and compare with x coordinate
	ldr r3, [r2, #0]
	cmp r0, r3
	movhs pc, lr

	// load the address of the framebuffer itself, add (y * width + x) * 2 to it, which gives the address in r2
	ldr r2, [r2, #32]
	mla r0, r1, r3, r0
	add r2, r0, lsl #1

	// load the colour to store
	ldr r3, =foreColour
	ldrh r3, [r3]

	strh r3, [r2]
	mov pc, lr

/* DrawLine: Given to sets of coordinates, draws a straight line between them using Bresenham's algorithm
 * r0: x0
 * r1: y0
 * r2: x1
 * r3: y1
 */
.globl DrawLine
DrawLine:
	push {r4 - r12, lr}
	x0 .req r9
	x1 .req r10
	y0 .req r11
	y1 .req r12

	mov x0, r0
	mov x1, r2
	mov y0, r1
	mov y1, r3

	dx .req r4
	dyn .req r5 // negative of dy
	sx .req r6
	sy .req r7
	err .req r8

	cmp x0, x1
	subgt dx, x0, x1
	movgt sx, #-1
	suble dx, x1, x0
	movle sx, #1

	cmp y0, y1
	subgt dyn, y1, y0
	movgt sy, #-1
	suble dyn, y0, y1
	movle sy, #1

	add err, dx, dyn
	add x1, sx
	add y1, sy

	pixelLoop$:
		teq x0, x1
		teqne y0, y1
		popeq {r4 - r12, pc}

		mov r0, x0
		mov r1, y0
		bl DrawPixel

		cmp dyn, err, lsl #1
		addle err, dyn
		addle x0, sx

		cmp dx, err, lsl #1
		addge err, dx
		addge y0, sy

		b pixelLoop$
	
	.unreq x0
	.unreq x1
	.unreq y0
	.unreq y1
	.unreq dx
	.unreq dyn
	.unreq sx
	.unreq sy
	.unreq err

/* DrawByte: writes 8 bits in a row (in the framebuffer, at least, that's the most sensible usage)
 * r0: lower byte is written
 * r1: x position
 * r2: y position
 */
.globl DrawByte
DrawByte:
	// verify arguments
	and r0, r0, #0xFF
	cmp r1, #0x400
	cmplo r2, #0x300
	movhs pc, lr

	push {r4 - r7, lr}
	b8towr8 .req r4
	xPos .req r5
	yPos .req r6
	count .req r7
	mov b8towr8, r0
	mov xPos, r1
	mov yPos, r2
	mov count, #0
	 
	DrawByteLoop$:
		tst b8towr8, #1
		addne r0, xPos, count
		movne r1, yPos
		blne DrawPixel
		lsr b8towr8, #1

		add count, #1
		teq count, #8
		bne DrawByteLoop$
	
	pop {r4 - r7, pc}
	.unreq b8towr8
	.unreq xPos
	.unreq yPos
	.unreq count

.section .data
.align 4
font:
	.incbin "font0.bin"

.section .text
/* DrawCharacter: Draws a character. Wow.
 * r0: Character to be written
 * r1: x position
 * r2: y position
 */
.globl DrawCharacter
DrawCharacter:
	// verify arguments
	cmp r0, #127
	movhi pc, lr

	cmp r1, #0x400
	cmplo r2, #0x300
	movhs pc, lr

	push {r4 - r7, lr}
	xPos .req r4
	yPos .req r5
	charAddr .req r6
	mov xPos, r1
	mov yPos, r2

	ldr charAddr, =font
	add charAddr, charAddr, r0, lsl #4

	DrawCharacterLewp$:
		ldrb r0, [charAddr]
		mov r1, xPos
		mov r2, yPos
		bl DrawByte

		add yPos, #1
		add charAddr, #1
		tst charAddr, #0xF
		bne DrawCharacterLewp$

	// return character width and height:
	mov r0, #8
	mov r1, #16
	pop {r4 - r7, pc}
	.unreq xPos
	.unreq yPos
	.unreq charAddr

/* DrawString: Draws a string of specified length
 * r0: string
 * r1: length
 * r2: X position
 * r3: Y position
 */
.globl DrawString
DrawString:
	push {r4 - r9, lr}
	addr .req r4
	xPos .req r5
	yPos .req r6
	length .req r7
	xBase .req r8
	char .req r9

	mov addr, r0
	mov length, r1
	mov xPos, r2
	mov yPos, r3
	mov xBase, xPos

	DrawStringLoop$:
		subs length, #1
		poplt {r4 - r9, pc}

		ldrb char, [addr]
		mov r0, char
		mov r1, xPos
		mov r2, yPos
		bl DrawCharacter

		add addr, #1

		teq char, #'\n'
		addeq yPos, r1
		moveq xPos, xBase
		beq DrawStringLoop$

		teq char, #'\t'
		addne xPos, r0
		bne DrawStringLoop$

		add r0, r0, lsl #2
		x1 .req r1
		mov x1, xBase

		stringLoopTab$:
			add x1, r0
			cmp xPos, x1
			bge stringLoopTab$

		mov xPos, x1
		.unreq x1
		b DrawStringLoop$
	.unreq addr
	.unreq xPos
	.unreq yPos
	.unreq length
	.unreq xBase
	.unreq char
