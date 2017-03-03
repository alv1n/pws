#import "stdint.h"
#import "keyboard.h"

unsigned char modifiers;
unsigned char keys[6];
int is_modified;

unsigned char keys_old[6];


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
};

//Saves keys to variables (To be passed as function ptr)
void KeyPressedHandler(uint8_t ucModifiers, const unsigned char RawKeys[6])
{
    modifiers = ucModifiers;
    is_modified = 0;
    for(int i = 0;i <6;i++)
    {
            keys[i] = RawKeys[i];
    }
    return;
}

//Checks if Key was in scan
int KeyWasDown(uint16_t scanCode)
{
    for(int i=0;i<6;i++)
    {
        if(scanCode==keys[i])
        {
            return 1;
        }
    }
    return 0;
}

unsigned char KeyboardGetChar()
{
    for(int i=0;i<6;i++)
    {
        if(KeyWasDown(keys[i]) != 1)
        {
            if(keys[i] ==  0)
            {
                return 0;
            }
            if(keys[i] <= 103)
            {
                 uint8_t *modif;
                 if( (modifiers | 0b00100010) == 0) //Check if either shift is pressed
                 {
                    modif = KeysShift;
                 }
                 else
                 {
                    modif = KeysNormal;
                 }

                 if(modif[ keys[i] ] != 0)
                 {
                    return modif[ keys[i] ];
                 }
            }
        }
        return 0;
        
    }
}
