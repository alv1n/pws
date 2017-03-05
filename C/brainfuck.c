#include "asm.h"
#include "keyboard.h"
#include "print.h"
#include "scan.h"
#include "sleep.h"

char buf_bf[1000] = "+++[>,+.<-]";

uint8_t reel[1000];

void brainfuck() 
{
    for(int i = 0; i < 1000; i++)
    {
        reel[i] = 0;
    }
    PrintClear();
    int i = 0;
    int loc = 500;
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
                }
                break;
            default:
                break;
            }
        i++;
        for(int x = 0; x < CH_WIDTH; x++)
        {
            SetForeColour(0);
            DrawCharacter(127,x*8,700);
            DrawCharacter(127,x*8,684);
            SetForeColour(0xFFFF);

        }
        for(int x = 0; x < 40; x++)
        {
            char num[4];
            SignedString(reel[x+loc-20], num, 10);
            num[0] = ' ';
            DrawStringz(num, x*(8*4),700);
        }
        for(int x = 0; x < 40; x++)
        {
            DrawCharacter(buf_bf[x+i-20],x*8,684);
        }
        Sleep(2000000);
    }
}
