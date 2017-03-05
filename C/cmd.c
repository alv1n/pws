#include "scan.h"
#include "string.h"
#include "print.h"
#include "cmd.h"

#include "programs.h"

// number of chars on a screen
static char buf[CH_WIDTH * CH_HEIGHT];

void Cmd(void) 
{
	char ch;
	int i, lncnt = 0;

	for (;;)
	{
		i = 0;

		PrintFormat("[0x%x] >>> ", lncnt++);
		while ((ch = WaitChar()) != '\n' && i < sizeof(buf) -1)
		{
			if (ch == 27)		{
				i--;
				continue;
			} 
			else if (ch == ' ')
				continue;

			buf[i++] = ch;
			PrintCharacter(ch);
		}
		PrintCharacter('\n');
		buf[i] = '\0';

		if (!StringCompare("snake", buf))
		{
			snake();
		}
		else if (!StringCompare("notepad", buf))
		{
			PrintClear();
			Notepad();
		}
		else if (!StringCompare("brainfuck", buf))
		{
			brainfuck();
		}
		else if (!StringCompare("clear", buf))
		{
			PrintClear();
		}
		else if (!StringCompare("help", buf))
		{
			// defined in programs.h
			PRINT_CMDS(snake, notepad, brainfuck, clear, help);
		}
		else
		{
			PrintString("Ken ik niet lol\n");
		}			
	}
}
