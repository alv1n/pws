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


void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
    USPiEnvInitialize();
    USPiInitialize();

    USPiKeyboardAvailable();
    
    USPiKeyboardRegisterKeyStatusHandlerRaw(KeyPressedHandler);
    
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
    while(1)
    {
        char c = KeyboardGetChar();
        if(c != 0)
        {
             DrawCharacter(c,x,y);
             x += 8;
             if(x>=1024)
             {
                x = 0;
                y += 16;
             }
        }
    }
    
    
}

