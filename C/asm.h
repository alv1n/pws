#ifndef ASM_H
#define ASM_H

#include "stdint.h"
#include "graphics.h"

extern struct FrameBufferDescription{
    uint32_t height;
    uint32_t width;
    uint32_t vWidth;
    uint32_t vHeight;
    uint32_t pitch;
    uint32_t bitDepth;
    uint32_t x;
    uint32_t y;
    uint32_t *pointer;
    uint32_t size;
} FrameBufferDescription;

//Random.s
extern uint32_t Random(int seed); 

//Framebuffer.s
extern struct FrameBufferDescription* InitialiseFrameBuffer(int width, int height, int bitDepth);

//Drawing.s
extern uint16_t *foreColour;

extern void DrawPixel(uint8_t x, uint8_t y);

extern void SetForeColour(uint16_t col);

extern void SetGraphicsAddress(struct FrameBufferDescription *buffer);

extern void DrawCharacter(char character, uint32_t x, uint32_t y);

//text.s
extern int CharCount(const char *string);

extern int DrawStringz(char *string, uint32_t x, uint32_t y);

extern int SignedString(int num, char *dest, int base);

//GPIO.s
extern void SetGpioFunction(int pin, int function);

//Status is either 0 or 1
extern void SetGpio(int pin, int status);

//timer.s
extern void timerWait(int microseconds);

#endif
