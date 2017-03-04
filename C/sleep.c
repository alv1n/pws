void sleep(int mcsec)
{
    int timer_start = *(int *)0x20003000;
    int timer_current = *(int *)0x20003000;
    while(timer_start + mcsec <= timer_start)
    {
        timer_current = *(int *)0x20003000;
    }
}
