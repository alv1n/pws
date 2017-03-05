#include "print.h"
#include "asm.h"
#include "keyboard.h"
#include "scan.h"

#define ESC 27
#define INSERT 0
#define NORMAL 1

static char notepadBuffer[CH_WIDTH * CH_HEIGHT];
unsigned int cursor = 0;

void Notepad()
{
    int mode = INSERT;
    char c;
    while(c = GetChar())
    {
        if(c == ESC)
        {
            mode = mode ^ 1; 
        }

        if(mode == NORMAL)
        {
            switch(c)
            {
                case 'h':
                    cursor = (cursor - 1) < 0 ? 0 : (cursor - 1);
                    break;
                          
                case 'k':
                    break;
                
                case 'j':
                    break;
                
                case 'l':
                    if(notepadBuffer[cursor+1] != '\0')
                    {
                        cursor++;
                    }
                    break;

                case 'x': //Delete
                    for(int i=cursor;notepadBuffer[i] != '\0';i++)
                    {
                        notepadBuffer[i] = notepadBuffer[i+1];
                    } 
                    break;

                case 127: //Backspace
                    break; 

                default:
                    break;
        }
            if(mode == INSERT)
            {
                if(c > 31 && c < 127)
                {
                    notepadBuffer[cursor] = c;
                }
            }
        }
    }
}
