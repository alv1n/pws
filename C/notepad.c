#include "print.h"
#include "asm.h"
#include "keyboard.h"
#include "scan.h"
#include "misc.h"

#define ESC 27
#define INSERT 0
#define NORMAL 1
#define INSERT_COL 0xF800 //RED
#define NORMAL_COL 0x001F //NOT RED

#define CURSOR_I -1
#define CURSOR_N -2

static char buf[CH_WIDTH * CH_HEIGHT];
unsigned int cursor = 0;
int mode = NORMAL;

void NormalMode(char c);
void InsertMode(char c);
void DrawCursor(void);

void Notepad()
{
    char c;
    while(1)
    {
        if(new_input)
        {
            new_input = 0;
            c = GetChar();
            if(c == ESC)
            {
                mode = mode ^ 1; 
            }

            if(mode == NORMAL)
            {
                NormalMode(c);
            }
            else
            {
                InsertMode(c);
            }
        }

        DrawCursor();

        // buf is ready, update screen
        ClearScreen();
        PrintString(buf);
    }
}

void DrawCursor()
{
    switch(mode)
    {
        case INSERT:
            buf[cursor] = CURSOR_I;
            break;
        case NORMAL:
            buf[cursor] = CURSOR_N;
            break;
        default:
            break;
    }
} 

void InsertMode(char c)
{
    if(c > 31 && c < 127)
    {
        MemoryMove(buf+cursor,buf+cursor+1,CharCount(buf+cursor)+1);
        buf[cursor] = c;
        cursor++;
    }
}


void NormalMode(char c)
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
        if(buf[cursor+1] != '\0')
        {
            cursor++;
        }
        break;

    case 'x': //Delete
        MemoryMove(buf+cursor,buf+cursor+1,CharCount(buf+cursor+1)+1);
        break;

    case 127: //Backspace
        MemoryMove(buf+cursor-1,buf+cursor,1+CharCount(buf+cursor));
        break; 

    default:
        break;
    }
}
