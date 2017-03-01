##############################################################################
#	makefile
#	 by Alex Chadwick, Ket Bottelier en Alvin Reumer
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
C_SRC = C/
ASM_SRC = asm/

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

#CFLAGS
CFLAGS += -W

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
ASM_OBJECTS := $(patsubst $(ASM_SRC)%.s, $(BUILD)%.o, $(wildcard $(ASM_SRC)*.s))

C_OBJECTS := $(patsubst $(C_SRC)%.c, $(BUILD)%.o, $(wildcard $(C_SRC)*.c))

# NEW usb driver library
LIBRARIES := libuspi.a libuspienv.a

# Include headers
HEADERS := /include

# Rule to make everything.
all: clean $(TARGET) $(LIST) 
#	cp kernel.img /media/kindo/boot/kernel.img

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
#$(BUILD)output.elf : $(ASM_OBJECTS) $(C_OBJECTS) $(LINKER) 
#	$(ARMGNU)-ld --no-undefined $(C_OBJECTS) $(ASM_OBJECTS) -L. $(patsubst %, -l %, $(LIBRARIES)) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)
$(BUILD)output.elf : $(ASM_OBJECTS) $(C_OBJECTS) $(LINKER) 
	$(ARMGNU)-ld --no-undefined $(C_OBJECTS) $(ASM_OBJECTS) -L. $(patsubst %, %, $(LIBRARIES)) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the object files.
$(BUILD)%.o: $(ASM_SRC)%.s $(BUILD)
	$(ARMGNU)-as -I $(ASM_SRC) $< -o $@

$(BUILD)%.o: $(C_SRC)%.c $(BUILD)
	$(ARMGNU)-gcc-5.4.0 -mfloat-abi=hard -I $(HEADERS) -c $< -o $@

$(BUILD):
	mkdir $@

# Rule to clean files.
clean : 
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
