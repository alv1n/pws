extern void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags);

void _cstartup(unsigned int r0, unsigned int r1, unsigned int r2)
{
    kernel_main( r0, r1, r2);

}
