#include "graphics.h"
#include "asm.h"

void DrawPixelColor(int x, int y, uint16_t col)
{
    SetForeColour(col);
    DrawPixel(x,y);
    SetForeColour(0xFFFF);
    return;
}

void ClearScreen()
{
    for(int x=0;x<1024;x++)
    {
        for(int y=0;y<768;y++)
        {
            DrawPixelColor(x,y,0);
        }
    }
    return;
}

int ReadPixel(int x,int y) //Read a pixel colour from the screen
{
    uint32_t *frameAddr = (frameRet->pointer + (x + y*768)*2);
    return *frameAddr; 
}
