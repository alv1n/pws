#include "../include/uspi.h"
#include "../include/uspios.h"
//#include "../include/uspienv.h"
//#include "../include/util.h"
#include "stdint.h"
#include "asm.h"

//Modifiers and last 6 keys pressed
unsigned char modifiers;
unsigned char keys[6];

/*
static void KeyPressedHandler(unsigned char modif, const unsigned char *pString)
{
    DrawStringz(pString,0,0);
}
*/
static void KeyPressedHandler(const char *pString)
{
    ScreenDeviceWrite( USPiEnvGetScreen(), pString, strlen(pString));
}


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
    
    DrawStringz("Screen turned on succesfully!",0,0);
    timerWait(5000000);
    USPiEnvInitialize(); 
    USPiInitialize();

    USPiKeyboardAvailable();
    int loc = 0; 
    
    USPiKeyboardRegisterKeyPressedHandler(KeyPressedHandler);
    while(1)
    {
        timerWait(10000000);
    }
}

