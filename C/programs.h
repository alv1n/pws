#ifndef PROGRAMS_H
#define PROGRAMS_H

//Snake.c
extern void snake();

extern void brainfuck(void);


extern void Paint(void);

extern void Notepad(void);


#define PRINT_CMDS(...) PrintFormat("Available arguments:\n\t" #__VA_ARGS__ "\n")
#endif
