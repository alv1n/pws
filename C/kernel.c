#include "../include/uspi.h"
#include "../include/uspios.h"
#include "../include/uspienv.h"

#include "stdint.h"
#include "asm.h"
#include "keyboard.h"
#include "programs.h"
#include "graphics.h"
#include "print.h"
#include "sleep.h"
#include "programs.h"
#include "cmd.h"

struct FrameBufferDescription *frameRet;

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
    //Initalise driver
    USPiEnvInitialize();
    USPiInitialize();
    USPiKeyboardAvailable();
    USPiKeyboardRegisterKeyPressedHandler(KeyboardHandler);

    frameRet = InitialiseFrameBuffer(1024, 768, 16);
    //If Initialised correctly enable LED 
    if (frameRet != 0)
    {
        SetGpioFunction(16,1);
        SetGpio(47,0);
    }
    SetGraphicsAddress(frameRet);

    //Cmd();
    Sleep(1000000);
    PrintCharacter('a');
    Sleep(1000000);

    PrintCharacter('b');
    Sleep(1000000);
    
    PrintCharacter('c');
    Sleep(1000000);
    while(1)
    {
        PrintCharacter('d');
        Sleep(1000000);
    }
} 

