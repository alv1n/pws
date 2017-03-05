#include "scan.h"
#include "string.h"
#include "print.h"
#include "cmd.h"

#include "programs.h"

// number of chars on a screen
static char buf_cmd[CH_WIDTH * CH_HEIGHT];

void Cmd(void) 
{
	char ch;
	int i, lncnt = 0;

	for (;;)
	{
		i = 0;

		PrintFormat("[0x%x] >>> ", lncnt++);
		while ((ch = WaitChar()) != '\n' && i < sizeof(buf_cmd) -1)
		{
			if (ch == 127) {
				i--;

			} 
			else if (ch == ' ')
				continue;
			else
				buf_cmd[i++] = ch;

			PrintCharacter(ch);
		}
		PrintCharacter('\n');
		buf_cmd[i] = '\0';

		if (!StringCompare("snake", buf_cmd))
		{
			snake();
		}
		else if (!StringCompare("notepad", buf_cmd))
		{
			PrintClear();
			Notepad();
		}
		else if (!StringCompare("brainfuck", buf_cmd))
		{
			brainfuck();
		}
        else if (!StringCompare("paint",buf_cmd))
        {
            Paint();
        }
		else if (!StringCompare("clear", buf_cmd))
		{
			PrintClear();
		}
		else if (!StringCompare("help", buf_cmd))
		{
			// defined in programs.h
			PRINT_CMDS(paint, snake, notepad, brainfuck, clear, help);
		}
		else
		{
			PrintString("Syntax Error!\n");
		}			
	}
}
