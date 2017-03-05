#include "stdint.h"
#include "asm.h"
#include "keyboard.h"
#include "programs.h"
#include "print.h"
#include "scan.h"

int get_input;

uint16_t colours[9] = 
{
    0x0000, 0x7FFF, 0xFFFF,\
    0xF800, 0x07E0, 0x001F,\
    0x1304, 0x5F23, 0xA23B,\
};

int x = 100;
int y = 100;
int col = 0xFFFF;
int size = 4;

void DrawPoint();

void Paint()
{
    PrintClear();
    while(1)
    {
        while(!get_input)
        {
            SetForeColour(x ^ 0xFE12);
            DrawPixel(x,y);
        }
        get_input = 0;
        char c = GetChar();
        switch(c)
        {
            case ' ':
                DrawPoint();
                break;
            case '+':
                size+=4;
                break;
            case '-':
                size-=4;
                break;
            case 'w':
                if(y - (size >> 1) > 0)
                {
                    y -= (size >> 1);
                }
                break;
            case 's':
                if(y + (size >> 1) < 768)
                {
                    y += (size >> 1);
                }
                break;
            case 'a':
                if(x - (size >> 1) > 0)
                {
                    x -= (size >> 1);
                }
                break;
            case 'd':
                if(x + (size >> 1) < 1024)
                {
                    x += (size >> 1);
                }
                break;
            case 'q':
                return;
            default:
                break;
        }
        if(c >= '1' && c <= '9')
        {
            col = colours[c - '1'];
        }
    }
}

void DrawPoint()
{
    for(int i = 0;i < size;i++)
    {
        for(int j = 0; j < size; j++)
        {
            SetForeColour(col);
            DrawPixel(x,y);
        }
    }
}
