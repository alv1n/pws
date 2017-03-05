#include "stdint.h"
#include "keyboard.h"
#include "asm.h"

#define CH_WIDTH 128
#define CH_HEIGHT 48;

char lastPressed[1000];
int counter = 0;
int new_input = 0;

void KeyboardHandler(const char *pString)
{
    new_input = 1;
    static int i = 0;
    counter = counter + i;
    if(counter + 6>999)
    {
        counter = 0;
    }

    for(i = 0; i < CharCount(pString); i++)
    {
        lastPressed[counter+i] = pString[i];
    }
    lastPressed[counter+i] = '\0';
    lastPressedPos = counter+i;
}





/*
static const uint8_t KeysNormal[104] = 
{
     0x0, 0x0, 0x0, 0x0, 'a', 'b', 'c', 'd',
     'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
     'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
     'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
     '3', '4', '5', '6', '7', '8', '9', '0',
     '\n', 0x0, '\b', '\t', ' ', '-', '=', '[',
     ']', '\\', '#', ';', '\'', '`', ',', '.',
     '/', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
     '\n', '1', '2', '3', '4', '5', '6', '7',
     '8', '9', '0', '.', '\\', 0x0, 0x0, '='
};

static const uint8_t KeysShift[104] = 
{
     0x0, 0x0, 0x0, 0x0, 'A', 'B', 'C', 'D',
     'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
     'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"',
     '$', '$', '%', '^', '&', '*', '(', ')',
     '\n', 0x0, '\b', '\t', ' ', '_', '+', '{',
     '}', '|', '~', ':', '@', 'X', '<', '>',
     '?', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
     0x0, 0x0, 0x0, 0x0, '/', '*', '-', '+',
     '\n', '1', '2', '3', '4', '5', '6', '7',
     '8', '9', '0', '.', '|', 0x0, 0x0, '='
}; */
