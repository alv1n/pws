#include <stdint.h>
#include <stdarg.h>
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

void PrintUnsigned(unsigned num, unsigned base)
{
	if (num == 0)
	{
		return;
	}

	PrintUnsigned(num/base, base);

	PrintCharacter(digits[num % base]);
}

void PrintNumber(int num, unsigned base) 
{
	if (num < 0) 
	{
		num = -num;
		PrintCharacter('-');
	}

	PrintUnsigned(num, base);
}

void PrintFormat(const char *string, ...)
{
	va_list ap;

	va_start(ap, string);

	while (*string != '\0') 
	{
		if (*string == '%') 
		{
			string++;

			switch (*string++) 
			{
				case '\0': va_end(ap); return;
				case '%' : PrintCharacter('%'); break;
				case 'c' : PrintCharacter((char) va_arg(ap, int));
				case 'b' : PrintNumber(va_arg(ap, int), 2); break;
				case 'o' : PrintNumber(va_arg(ap, int), 8); break;
				case 'u' : PrintUnsigned(va_arg(ap, unsigned), 10); break;
				case 'd' :
				case 'i' : PrintNumber(va_arg(ap, int), 10); break;
				case 'x' : PrintNumber(va_arg(ap, int), 16); break;
				case 'p' : PrintUnsigned(va_arg(ap, unsigned), 16); break;
				default: break;
			}
		}
		else
		{
			PrintCharacter(*string++);
		}
	}

	va_end(ap);
	return;
}
