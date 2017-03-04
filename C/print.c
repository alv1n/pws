#include <stdint.h>
#include "asm.h"
#include "print.h"

// The width and height of the screen measured in chars
#define CH_WIDTH 128
#define CH_HEIGHT 48

static int x_pos = 0;
static int y_pos = 0;

void PrintCharacter(unsigned char ch)
{
	DrawCharacter(ch, x_pos * 8, y_pos * 16);

	x_pos++;
	if (x_pos >= CH_WIDTH) 
	{
		y_pos++;
		x_pos = 0;

		if (y_pos >= CH_HEIGHT)
		{
			x_pos = 0;
			y_pos = 0;
		}
	}
}


static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static void _PrintNumber(unsigned int num, unsigned int base)
{
	if (num == 0)
	{
		return;
	}

	_PrintNumber(num/base, base);

	PrintCharacter(digits[num % base]);
}

void PrintNumber(int num, unsigned int base) 
{
	if (num < 0) 
	{
		num = -num;
		PrintCharacter('-');
	}

	_PrintNumber(num, base);
}


