#include "asm.h"
#include "keyboard.h"
#include "print.h"
#include "scan.h"
#include "sleep.h"
#include "programs.h"

#define CH_WIDTH 128
#define CH_HEIGHT 48

//#define buf_bf buf

//Exit with backspace
char buf[CH_WIDTH * CH_HEIGHT];

char buf_bf[CH_WIDTH * CH_HEIGHT];

uint8_t reel[1000];

void brainfuck() 
{
    PrintClear();

    int i;
    for(i=0; buf[i] != '\0'; i++)
    {
        buf_bf[i] = buf[i];
    }
    buf_bf[i] = 0;


    int loc = 0;
    if(new_input && GetChar() == 127) 
    {
        PrintClear();
        return;
    }
    while(buf_bf[i] != 0)
    {
        switch(buf_bf[i])
        {
            case '>':
                loc++;
                break;
            case '<':
                loc = (loc - 1) < 0 ? 0 : loc - 1;
                break;
            case '+':
                reel[loc]++;
                break;
            case '-':
                reel[loc]--;
                break;
            case '[':
                break;
            case ']':
                if(reel[loc])
                {
                    int bracket_counter = 0;
                    for(int j=i;buf_bf[j] != 0; j--)
                    {
                        if(buf_bf[j] == ']')
                        {
                            bracket_counter--;
                        }
                        else if(buf_bf[j] == '[')
                        {
                            bracket_counter++;
                        }
                        if(bracket_counter == 0)
                        {
                            i = j;
                            break;
                        }
                    }
                }
                break;
            case '.':
                PrintCharacter(reel[loc]);
                break;
            case ',':
                while(new_input == 0)
                {
                }
                if(new_input == 1)
                {
                    new_input = 0;
                    reel[loc] = GetChar();
                    if(reel[loc] == 127)
                    {
                        PrintClear();
                        return;
                    }
                    
                }
                break;
            default:
                break;
            }
        i++;
        

        //Shows code being executed at the bottom
        for(int x = 0; x < 40 || buf_bf[x+i] == '\0'; x++)
        {
            if(buf_bf[x+i] <= 0)
            {
                break;
            }
            SetForeColour(0);
            DrawCharacter(127,x*8,752);
            SetForeColour(0xFFFF);
            DrawCharacter(buf_bf[x+i],x*8,752);
        }
        Sleep(2000000);
    }
}
