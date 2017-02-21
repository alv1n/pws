.section .data
tag_core: .int 0
tag_mem: .int 0
tag_videotext: .int 0
tag_ramdisk: .int 0
tag_initrd2: .int 0
tag_serial: .int 0
tag_revision: .int 0
tag_videolfb: .int 0
tag_cmdline: .int 0

.section .text
/* FindTag: returns address of the contents of the given tag, or zero if not found
 * r0: tag to find (1 - 9)
 * return value: address of tag contents, or zero
 */
.globl FindTag
FindTag:
	tag .req r0
	tagList .req r1
	tagAddr .req r2

	// return if tag > 9
	sub tag, #1
	cmp tag, #8
	movhi tag, #0
	movhi pc, lr

	// tag_core is the start of our tag contents address list
	ldr tagList, =tag_core
	
	tagReturn$:
		add tagAddr, tagList, tag, lsl #2
		ldr tagAddr, [tagAddr]
	
		// if the tag address stored in the list is not zero, it is already known and can therefore be returned
		teq tagAddr, #0
		movne r0, tagAddr
		movne pc, lr
	
	// start with the first tag
	mov tagAddr, #0x100
	push {r4}
	tagIndex .req r3
	oldAddr .req r4
	tagLoop$:
		// if the tag index is zero, we've hit the last two zero-filled words if the tag field, so we can return
		ldrh tagIndex, [tagAddr, #4]
		subs tagIndex, #1
		poplt {r4}
		blt tagReturn$
		
		// Check if the current address value stored in our list (for this tag) is zero, if so, update it to our new address (tagAddr)
		add tagIndex, tagList, tagIndex, lsl #2
		ldr oldAddr, [tagIndex]
		teq oldAddr, #0
		.unreq oldAddr
		streq tagAddr, [tagIndex]

		// add the size of the tag in words to the current tag address, so tagAddr points to the next tag
		ldr tagIndex, [tagAddr]
		add tagAddr, tagIndex, lsl #2

	.unreq tag
	.unreq tagList
	.unreq tagAddr
	.unreq tagIndex
