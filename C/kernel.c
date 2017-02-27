#include "../include/uspi.h"
#include "stdint.h"
#include "asm.h"
/*
struct FrameBufferDescription{
    uint32_t height;
    uint32_t width;
    uint32_t vWidth;
    uint32_t vHeight;
    uint32_t pitch;
    uint32_t bitDepth;
    uint32_t x;
    uint32_t y;
    uint32_t pointer;
    uint32_t size;
};
*/
struct FrameBufferDescription FramebufferInfo =
    { 1024, 768, 1024, 768, 0, 24, 0, 0, 0, 0 };

char str[] = "Lolz";

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
    struct FrameBufferDescription* frameRet = InitialiseFrameBuffer(1024, 768, 16);
    //If Initialized correctly enable LED 
    if (frameRet != 0)
    {
        SetGpioFunction(16,1);
        SetGpio(47,0);
    }

    SetGraphicsAddress(frameRet);
    while(1){
        DrawCharacter('A',120,120);
        DrawString(str,4,100,100);
    }
}

