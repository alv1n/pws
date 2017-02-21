.section .data
.align 4 // Ensure that lowest four bits of fbInfo address are 0, allowing it to be sent via mailbox
.globl FrameBufferInfo
FrameBufferInfo:
	.int 1024 // #0 Physical Width
	.int 768  // #4 Physical Height
	.int 1024 // #8 Virtual Width
	.int 768  // #12 Virtual Height
	.int 0    // #16 GPU - Pitch (Number of bytes in a row of the framebuffer)
	.int 16   // #20 Bit depth
	.int 0    // #24 X
	.int 0    // #28 Y
	.int 0    // #32 GPU - Pointer
	.int 0    // #36 GPU - Size

.section .text
/* InitialiseFramebuffer: ... initialises frame buffer.
 * r0: width
 * r1: height
 * r2: bit depth
 * returns pointer to framebuffer, 0 if not successful
 */
.globl InitialiseFrameBuffer
InitialiseFrameBuffer:
	cmp r0, #4096
	cmpls r1, #4096
	cmpls r2, #32
	movhi r0, #0
	movhi pc, lr
	
	// function calls coming up, r4 = working value
	push {r4, lr}
	ldr r4, =FrameBufferInfo
	str r0, [r4, #0]
	str r1, [r4, #4]
	str r0, [r4, #8]
	str r1, [r4, #12]
	str r2, [r4, #20]
	
	// request GPU by sanding fbinfo address
	mov r0, r4
	add r0, #0x40000000
	mov r1, #1
	bl MailboxWrite

	// Check GPU's reply
	mov r0, #1
	bl MailboxRead
	teq r0, #0
	movne r0, #0
	popne {r4, pc}

	mov r0, r4
	pop {r4, pc}
	
