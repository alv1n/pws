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
	int i;

	for (;;)
	{
		i = 0;

		PrintString(">>> ");
		while ((ch = WaitChar()) != '\n')
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
			Notepad();
		}
		else if (!StringCompare("brainfuck", buf))
		{
			brainfuck();
		}
        else if (!StringCompare("paint",buf))
        {
            Paint();
        }
		else
		{
			PrintString("Ken ik niet lol\n");
		}			
			
	}
}
