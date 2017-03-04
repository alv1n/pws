#include "../include/uspi.h"
#include "../include/uspios.h"
#include "../include/uspienv.h"

#include "stdint.h"
#include "asm.h"
#include "keyboard.h"
#include "programs.h"
#include "graphics.h"
#include "print.h"


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

    PrintFormat("This is a test: %d, %x, %o, %b", -10, 16, 8, 2);
    
    int x = 0;
    int y = 16;
    while(1)
    {   
        if(new_input)
        {
            new_input = 0;
            x+= 8*DrawStringz(lastPressed+counter,x,y);
            if(x>1024)
            {
                x = 0;
                y+=16;
                if(y > 768)
                {
                    y = 0;
                }
                
            }
        }
    }
}

