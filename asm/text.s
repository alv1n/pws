/* DrawStringz: Draws a null terminated string. Wrapper for DrawString.
 * r0: null-terminated string.
 * r1: x position
 * r2: y position
 */
.globl DrawStringz
DrawStringz:
	push {r4 - r6, lr}

	mov r4, r0
	mov r5, r1
	mov r6, r2

	bl CharCount

	mov r1, r0
	mov r0, r4
	mov r2, r5
	mov r3, r6
	bl DrawString

	pop {r4 - r6, pc}

/* r0: string address
 * returns number of characters in a null-terminated string
 */
.globl CharCount
CharCount:
	mov r1, r0
	mov r0, #0
	CharCountLoop$:
		ldrb r2, [r1, r0]
		cmp r2, #0
		moveq pc, lr

		add r0, #1
		b CharCountLoop$

/* r0: Number to convert
 * r1: Destination string
 * r2: Conversion base
 * returns number of characters written
 */
.globl SignedString
SignedString:
	push {r4, lr}

	cmp r2, #0
	movle r0, #-2
	pople {r4 - r12, pc}

	mov r4, #0
	cmp r0, #0
	bge ContinueSignedString$

	mov r3, #'-'
	teq r1, #0
	strneb r3, [r1]
	add r1, #1
	rsb r0, r0, #0
	add r4, #1

	ContinueSignedString$:
	bl UnsignedString
	add r0, r4
	pople {r4, pc}


/* r0: Number to convert
 * r1: Destination string
 * r2: Conversion base
 * returns number of characters written
 */
.globl UnsignedString
UnsignedString:
	push {r4 - r12, lr}

	mov r4, r0
	mov r5, r1
	mov r6, r2
	mov r7, #0

	ConversionLoop$:
		mov r1, r6
		bl DivideU32

		cmp r1, #10
		addlo r1, #'0'
		addhs r1, #('a'-10)
		
		teq r5, #0
		strneb r1, [r5, r7]

		add r7, #1
		cmp r0, #0
		bhi ConversionLoop$

	teq r5, #0
	movne r0, r5
	movne r1, r7
	blne ReverseString
	mov r0, r7
	pop {r4 - r12, pc}

/* r0: string address
 * r1: length
 */
.globl ReverseString
ReverseString:
	add r1, r0, r1
	sub r1, #1

	ReversionLoop$:
		cmp r1, r0
		movls pc, lr

		ldrb r2, [r0]
		ldrb r3, [r1]

		strb r3, [r0]
		strb r2, [r1]

		add r0, #1
		sub r1, #1
		b ReversionLoop$
/* r0: format string
 * r1: length
 * r2: destination
 * r3 and stack: format arguments
 */
.globl FormatString
FormatString:
	format .req r4
	formatLength .req r5
	dest .req r6
	nextArg .req r7
	argList .req r8
	length .req r9

	push {r4,r5,r6,r7,r8,r9,lr}
	mov format,r0
	mov formatLength,r1
	mov dest,r2
	mov nextArg,r3
	add argList,sp,#7*4
	mov length,#0

	formatLoop$:

	subs formatLength,#1
	movlt r0,length
	poplt {r4,r5,r6,r7,r8,r9,pc}

	ldrb r0,[format]
	add format,#1
	teq r0,#'%'
	beq formatArg$

	formatChar$:

	teq dest,#0
	strneb r0,[dest]
	addne dest,#1
	add length,#1
	b formatLoop$

	formatArg$:

	subs formatLength,#1
	movlt r0,length
	poplt {r4,r5,r6,r7,r8,r9,pc}

	ldrb r0,[format]
	add format,#1
	teq r0,#'%'
	beq formatChar$

	teq r0,#'c'
	moveq r0,nextArg
	ldreq nextArg,[argList]
	addeq argList,#4
	beq formatChar$

	teq r0,#'s'
	beq formatString$

	teq r0,#'d'
	beq formatSigned$

	teq r0,#'u'
	teqne r0,#'x'
	teqne r0,#'b'
	teqne r0,#'o'
	beq formatUnsigned$

	b formatLoop$

	formatString$:

	ldrb r0,[nextArg]
	teq r0,#0x0
	ldreq nextArg,[argList]
	addeq argList,#4
	beq formatLoop$
	add length,#1
	teq dest,#0
	strneb r0,[dest]
	addne dest,#1
	add nextArg,#1
	b formatString$

	formatSigned$:

	mov r0,nextArg
	ldr nextArg,[argList]
	add argList,#4
	mov r1,dest
	mov r2,#10
	bl SignedString
	teq dest,#0
	addne dest,r0
	add length,r0
	b formatLoop$

	formatUnsigned$:

	teq r0,#'u'
	moveq r2,#10
	teq r0,#'x'
	moveq r2,#16
	teq r0,#'b'
	moveq r2,#2
	teq r0,#'o'
	moveq r2,#8

	mov r0,nextArg
	ldr nextArg,[argList]
	add argList,#4
	mov r1,dest
	bl UnsignedString
	teq dest,#0
	addne dest,r0
	add length,r0
	b formatLoop$
