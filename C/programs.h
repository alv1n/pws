#ifndef PROGRAMS_H
#define PROGRAMS_H

//Snake.c
#define CH_WIDTH 128
#define CH_HEIGHT 48

extern void snake();

extern void brainfuck(void);

extern void Paint(void);

extern void Notepad(void);

extern char buf[CH_WIDTH * CH_HEIGHT];

#define PRINT_CMDS(...) PrintFormat("Available arguments:\n\t" #__VA_ARGS__ "\n")
#endif
