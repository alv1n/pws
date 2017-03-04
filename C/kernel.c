#include "../include/uspi.h"
#include "../include/uspios.h"

#include "stdint.h"
#include "asm.h"
#include "keyboard.h"
#include "programs.h"
#include "graphics.h"


void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
    USPiEnvInitialize();
    USPiInitialize();

    USPiKeyboardAvailable();
    
    USPiKeyboardRegisterKeyPressedHandler(KeyboardHandler);

    struct FrameBufferDescription* frameRet = InitialiseFrameBuffer(1024, 768, 16);
    //If Initialized correctly enable LED 
    if (frameRet != 0)
    {
        SetGpioFunction(16,1);
        SetGpio(47,0);
    }

    SetGraphicsAddress(frameRet);
    
    DrawStringz("Screen turned on succesfully!",0,0);
    int x = 0;
    int y = 16;
    while(1);
}

