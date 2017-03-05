#include "stdint.h"

#define addr 0x20003004

void Sleep(int mcsec)
{
    uint8_t timer_start = *(int *)addr;
    uint8_t timer_current = *(int *)addr;
    while(timer_start + mcsec <= timer_current)
    {
        timer_current = *(int *)addr;
    }
    return;
}
