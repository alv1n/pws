.section .data
tag_core .int 0
tag_mem .int 0
tag_videotext: .int 0
tag_ramdisk: .int 0
tag_initrd2: .int 0
tag_serial: .int 0
tag_revision: .int 0
tag_videolfb: .int 0
tag_cmdline: .int 0

.section .text
/* FindTag: Finds tag of given tag index. Or it fails. LOL.
 * r0: tag index to find, ranging from 1 - 9
 * returns the address of the given tag
 */
.globl
