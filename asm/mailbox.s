// Address and ofsets of mailbox channel:
.equ MAILBOX_BASE, 0x2000B880
.equ READ_OFF, 0x0
.equ POLL_OFF, 0x10
.equ SNDR_OFF, 0x14
.equ STAT_OFF, 0x18
.equ CONF_OFF, 0x1C
.equ WRITE_OFF, 0x20

/* MailboxWrite: write a message to a channel
 * r0: message to write, lower four bits 0
 * r1: channel to write to, 0 - 15
 */
.globl MailboxWrite
MailboxWrite:
	// Check arguments
	tst r0, #0xF
	movne pc, lr
	cmp r1, #15
	movhi pc, lr

	ldr r2, =MAILBOX_BASE

	wait1$:
		ldr r3, [r2, #STAT_OFF]
		tst r3, #0x80000000
		bne wait1$
	
	add r0, r0, r1
	str r0, [r2, #WRITE_OFF]
	mov pc, lr

/* MailboxRead: reads message from specified channel into r0
 * r0: channel to read from, 0 - 15
 */
.globl MailboxRead
MailboxRead:
	cmp r0, #15
	movhi pc, lr
	
	ldr r1, =MAILBOX_BASE

	rightmail$:
		wait2$:
			ldr r2, [r1, #STAT_OFF]
			tst r2, #0x40000000
			bne wait2$
		
		ldr r2, [r1, #READ_OFF]
		
		// Channel only
		and r3, r2, #0xF
		teq r3, r0
		bne rightmail$
	
	// clear channel information from message
	bic r0, r2, #0xF
	mov pc, lr

