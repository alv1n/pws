
extern uint32_t terminalStart; //First character that has been written in terminalBuffer
extern uint32_t terminalStop;  // Last character that has been written in terminalBuffer
extern uint32_t terminalView;  //First character present on screen
extern uint32_t terminalColour; //Colour to draw new characters with

//Higher 8 bytes ASCII code, lower 8 color
extern uint8_t terminalBuffer[128*128];
extern uint8_t terminalScreen [1024/8 * 768/16]; 



