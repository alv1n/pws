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

uint8_t x = 100;
uint8_t y = 100;
int col = 0xFFFF;
uint8_t size = 4;

void DrawPoint();

void Paint()
{
    PrintClear();
    while(1)
    {
        char c = WaitChar();
        get_input = 0;
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
            case '[':
                col -= 0x10;
                break;
            case ']':
                col += 0x10;
            case 'w':
                if(y < 0)
                {
                    y = 768;
                }
                y -= size;
                break;
            case 's':
                if(y > 768)
                {
                    y = 0;
                }
                y += size;
                break;
            case 'a':
                if(x < 0)
                {
                    x = 1024;
                }
                x -= size;
                break;
            case 'd':
                if(x > 1024)
                {
                    x = 0;
                }
                x +=size;
                break;
            case 'q':
                PrintClear();
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
            DrawPixel(x+i,y+j);
        }
    }
}
