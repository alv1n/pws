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
#include "calculator.h"

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
    //Enter code after this line:
    /*PrintFormat("This is a test: %d, %x, %o, %b", -10, 16, 8, 2);
    while(1)
    {
    	if (new_input)
	{
		new_input = 0;
		PrintString(lastPressed + counter);
	}
    }
    */

    Calculator();

}


