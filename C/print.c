#include <stdint.h>
//#include "../include/uspienv/stdarg.h"
#include <stdarg.h>
#include "asm.h"
#include "print.h"

// The width and height of the screen measured in chars
#define CH_WIDTH 128
#define CH_HEIGHT 48

static int prev_x_pos[CH_HEIGHT];
static int x_pos = 0;
static int y_pos = 0;

static void PrintNumber(int num, unsigned base);

void PrintCharacter(unsigned char ch)
{
	if (ch > 31 && ch < 127)
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
	else 
	{
		int tmp_x;

		switch (ch) 
		{
			case 127:
				(x_pos - 1) < 0 ? (y_pos--, x_pos = prev_x_pos[y_pos]) : x_pos--;
				SetForeColour(0);
				DrawCharacter(127, x_pos * 8, y_pos * 16);
				SetForeColour(0xFFFF);
				break;
			case '\n':
				prev_x_pos[y_pos++] = x_pos;
				x_pos = 0;
				break;
			case '\t':
				tmp_x = 0;
				while (tmp_x <= x_pos)
					tmp_x += 8;
				x_pos = tmp_x >= CH_WIDTH ? 0 : tmp_x;
				break;
			// Useful for checking the numbers of the key you're pressing
			default:
				PrintNumber((int) ch, 10);
				break;
		}
	}

}


void PrintString(const char *string)
{
	while (*string != '\0')
	{
		PrintCharacter(*string++);
	}
}
		


static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static void PrintUnsigned(unsigned num, unsigned base)
{
	if (num == 0)
	{
		return;
	}

	PrintUnsigned(num/base, base);

	PrintCharacter(digits[num % base]);
}

static void PrintNumber(int num, unsigned base) 
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

