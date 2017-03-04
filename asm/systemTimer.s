.equ TIMER_ADDR, 0x20003000
.equ CTRL_OFF, 0x0
.equ CNTR_OFF, 0x4
.equ CMPR0_OFF, 0xC
.equ CMPR1_OFF, 0x10
.equ CMPR2_OFF, 0x14
.equ CMPR3_OFF, 0x18

/* timerWait: waits at least the amount of microseconds specified
 * r0: #microseconds
 */
.globl timerWait
timerWait:
	// Save argument in r3
    push {r3}
	mov r3, r0

	// Load counter value
	ldr r2, =(TIMER_ADDR + CNTR_OFF)
	ldrd r0, r1, [r2]

	// Set goal value
	add r3, r3, r0

	timerWaitLoop$:
		ldrd r0, r1, [r2]
		cmp r3, r0
		bhi timerWaitLoop$

	// Return 
    pop {r3}
	mov pc, lr
