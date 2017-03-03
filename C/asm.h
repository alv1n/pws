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
};

//Random.s
extern uint32_t Random(int seed); 

//Drawing.s
extern uint16_t *foreColour;

extern void SetForeColour(uint16_t col);

extern void SetGraphicsAddress(struct FrameBufferDescription *buffer);

extern void DrawCharacter(char character, uint32_t x, uint32_t y);

//text.s
extern void DrawStringz(char *string, uint32_t x, uint32_t y);

extern int SignedString(int num, char *dest, int base);

//Framebuffer.s
extern struct FrameBufferDescription* InitialiseFrameBuffer(int width, int height, int bitDepth);

//GPIO.s
extern void SetGpioFunction(int pin, int function);

//Status is either 0 or 1
extern void SetGpio(int pin, int status);

//timer.s
extern void timerWait(int microseconds);


