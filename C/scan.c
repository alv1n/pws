#include "keyboard.h"
#include <string.h>

int lastPressedPos;

char GetChar(void)
{
	return lastPressed[lastPressedPos-1];
}

char WaitChar(void)
{
	while (1)
	{
		if (new_input)
		{
			new_input = 0;
			break;
		}

	}

	return GetChar();
}

static int IsNumber(int ch)
{
	return (ch >= 48 && ch <= 57);

}
unsigned ReadUnsigned(void)
{
	int ret_val = 0;
	char ch;

	while (1) 
	{
		if (new_input)
		{
			ch = GetChar();

			if (!IsNumber(ch))
			{
				return 0;
			}
			
			ret_val *= 10;
			ret_val += ((int) ch - '0');
		}
	}

	return ret_val;
}


