#include "keyboard.h"
int lastPressedPos;

char GetChar()
{
    return lastPressed[lastPressedPos-1];
}
