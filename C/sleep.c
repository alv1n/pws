#include "stdint.h"

#define addr 0x20003004

//Not working
void Sleep(int mcsec)
{
    uint32_t timer_start = *(int *)addr;
    uint32_t timer_current = *(int *)addr;
    while(timer_start + mcsec <= timer_current)
    {
        timer_current = *(int *)addr;
    }
    return;
}
