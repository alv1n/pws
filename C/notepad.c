#include "print.h"
#include "asm.h"
#include "keyboard.h"
#include "scan.h"
#include "misc.h"

#define ESC 27
#define INSERT 0
#define NORMAL 1
#define INSERT_COL 0xF800 //RED
#define NORMAL_COL 0x001F //BLUE

#define CURSOR_I -1
#define CURSOR_N -2

static char buf[CH_WIDTH * CH_HEIGHT];
int cursor = 0;
int mode = INSERT;

void NormalMode(char c);
void InsertMode(char c);
void DrawCursor(void);

static char under_cursor= 0;


void Notepad()
{
    char c;
    while(1)
    {
        if(new_input)
        {
            new_input = 0;
            c = GetChar();
            if(c == '\\')
            {
                mode = mode ? INSERT : NORMAL;
            }
            else if(mode == NORMAL)
            {
                NormalMode(c);
            }
            else
            {
                InsertMode(c);
            }
            DrawCursor();
            PrintClear();
            PrintString(buf);
            DrawCharacter(under_cursor,0,400);
            char cur[4];
            UnsignedString(cursor,cur,10);
            DrawStringz(cur,0,416);

        }
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
    return;
}


void NormalMode(char c)
{
    switch(c)
    {
    case 'h':
        cursor = (cursor - 1) <= 0 ? 0 : (cursor - 1);
        buf[cursor+1] = under_cursor;
        under_cursor = buf[cursor];
        break;
    case 'k':
        break;

    case 'j':
        break;

    case 'l':
        if(buf[cursor] != '\0')
        {
            // 'elegantie'
            buf[cursor++] = under_cursor;
            under_cursor = buf[cursor];
        } break;

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
