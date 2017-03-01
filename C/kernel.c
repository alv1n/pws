#include "../include/uspi.h"
#include "../include/uspios.h"
//#include "../include/uspienv.h"
//#include "../include/util.h"
#include "stdint.h"
#include "asm.h"
#include "keyboard.h"

//Modifiers and last 6 keys pressed
unsigned char modifiers;
unsigned char keys[6];

void modKeys(unsigned char ucModifiers, const unsigned char RawKeys[6])
{
    modifiers = ucModifiers;
    for(int i = 0;i <6;i++)
    {
        keys[i] = RawKeys[i];
    }
    return;
}

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
    USPiEnvInitialize();
    USPiInitialize();

    USPiKeyboardAvailable();
    
    USPiKeyboardRegisterKeyStatusHandlerRaw(modKeys);
    
    struct FrameBufferDescription* frameRet = InitialiseFrameBuffer(1024, 768, 16);
    //If Initialized correctly enable LED 
    if (frameRet != 0)
    {
        SetGpioFunction(16,1);
        SetGpio(47,0);
    }

    SetGraphicsAddress(frameRet);
    
    DrawStringz("Screen turned on succesfully!",0,0);
    
    int loc = 8;
    while(1)
    {
        for(int i=0; i < 6; i++)
        {
            char str[3];
            SignedString(keys[i],str,10);
            DrawStringz(str,loc,0);
            loc += 8*3;
            timerWait(1000000);
        }

    }
    
    
}

