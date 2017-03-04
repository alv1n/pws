
extern unsigned char modifiers;
extern unsigned char keys[6];

void func(const unsigned char *pString);
    
extern int is_modified;

extern void KeyPressedHandler(unsigned char ucModifiers, const unsigned char RawKeys[6]);

extern int KeyWasDown(uint16_t scanCode);

extern unsigned char KeyboardGetChar();
