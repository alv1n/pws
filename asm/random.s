/* Random: Gives a random word using the input, which should be a previous output, preferably
 * r0: seed
 */
.globl Random
Random:
xnm .req r0
a .req r1

mov a, #0xef00
mul a, xnm
mul a, xnm
add a, xnm
.unreq xnm
add r0, a, #73

.unreq a
mov pc, lr

