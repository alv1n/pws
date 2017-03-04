#include "stdint.h"
#include "asm.h"
#include "terminal.h"


uint32_t terminalStart = 0; //First character that has been written in terminalBuffer
uint32_t terminalStop = 0;  // Last character that has been written in terminalBuffer
uint32_t terminalView = 0;  //First character present on screen
//uint32_t terminalColour = 0xF;//Colour to draw new characters with

//Higher 8 bytes ASCII code, lower 8 color
uint8_t terminalBuffer[128*128];
uint8_t terminalScreen [1024/8 * 768/16]; 

/*
void TerminalColour(uint8_t colour) //0bxxxx, highest bit adds 1/3 to all, lower 2/3 to each RGB 
{
    uint8_t to_draw;
    if(colour == 6)
    {
        SetForeColour(0x02B5); //Brown 0b0110
        return;
    }
    if(colour & #0b1000)
    {
        to_draw = 0x52AA;
    }
    if(colour & #0b0100)
    {
        to_draw += 0x15;
    }
    if(colour & 0b0010)
    {
        to_draw += 0x540;
    }
    if(colour & 0b0001)
    {
        to_draw +=0xA800;
    }
    SetForeColour(to_draw);
    return;
}*/


void TerminalDisplay()
{
    uint16_t character;
    uint16_t *taddr = (uint16_t *)&terminalBuffer[terminalStart];
    uint16_t view = taddr[terminalView - terminalStart];
    uint16_t stop = taddr[terminalStop - terminalStart];
    uint16_t *screen = taddr;
    uint16_t col = screen[0];
    for(int y=0;y<768;y+=16)
    {
        for(int x=0;x<1024;x+=16)
        {
            if(terminalView != terminalStop)
            {
                character = view;
            }
            else
            {
                character = (0x7 << 8);
            }

            if(character != col)
            {
                *screen = character;
                
                //Background col
                //TerminalColour((character >> 12));
                DrawCharacter(0x7F,x,y);
                
                //Foreground col

            }
            
            screen += 2;
            if(view != stop)
            {
                view += 2;
            }
            if(view = terminalStop)
            {
                view = terminalStart;
            }

        }
    }
}
