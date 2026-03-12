TARGET			:= Sigma_io

RM				:= rm -rf

OBJDIR			:= OBJ
BSWDIR			:= BSW
APPDIR			:= APP
PLATFORMDIR		:= PLATFORM
RTEDIR			:= RTE

BUILD       := BUILD
ELF         := $(BUILD)/$(TARGET).elf
HEX         := $(BUILD)/$(TARGET).hex
BIN         := $(BUILD)/$(TARGET).bin
MAP         := $(BUILD)/$(TARGET).map

SRC_C		:= $(shell find $(BSWDIR) -type f -name "*.c")
SRC_C		+= $(shell find $(RTEDIR) -type f -name "*.c")
SRC_C		+= $(shell find $(APPDIR) -type f -name "*.c")
SRC_C		+= $(shell find $(PLATFORMDIR) -type f -name "*.c")
SRC_C		+= main.c
OBJ_C		:= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC_C))

SRC_S		:= $(shell find $(PLATFORMDIR) -type f -name "*.s")
OBJ_S		:= $(patsubst %.s, $(OBJDIR)/%.o, $(SRC_S))

OBJ			:= $(OBJ_C) $(OBJ_S)
DEP			:= $(OBJ:.o=.d)

INC_DIR		:= $(shell find $(BSWDIR) $(RTEDIR) $(APPDIR) $(RTEDIR) $(PLATFORMDIR) -type d -name "Inc*")
INC_DIR		+= $(shell find $(BSWDIR) $(RTEDIR) $(APPDIR) $(RTEDIR) $(PLATFORMDIR) -type d -name "Leg*")

INCLUDES	:= $(addprefix -I, $(INC_DIR))

LDSCRIPT	:= $(shell find $(PLATFORMDIR) -type f -name "*.ld")

PREFIX		:= arm-none-eabi-
CC			:= $(PREFIX)gcc
AS			:= $(PREFIX)gcc
OBJCOPY		:= $(PREFIX)objcopy
SIZE        := $(PREFIX)size

MCU			:= cortex-m4
FPU			:= fpv4-sp-d16
FLOAT_ABI	:= hard

MCUFLAGS	:= -mcpu=$(MCU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -mthumb
CSTD		:= -std=gnu11
DEBUG		:= -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx
OPT			:= -O0
SECT      	:= -ffunction-sections -fdata-sections -fstack-usage -fcyclomatic-complexity
DEPFLAGS  	:= -MMD -MP
WARN 		:= -Wall

CFLAGS    	:= $(MCUFLAGS) $(CSTD) $(DEBUG) $(INCLUDES) $(OPT) $(SECT) $(WARN) $(DEPFLAGS)

LDFLAGS   	:= $(MCUFLAGS) \
             -T$(LDSCRIPT) \
             -Wl,-Map=$(MAP),--cref \
             -Wl,--gc-sections \
             -specs=nano.specs -specs=nosys.specs

CUBEPROG 	:= STM32_Programmer_CLI.exe
CONNECT		:= -c
PORT		:= port=JLINK
ERASE		:= -e all
WRITE		:= -w
VERIFY		:= -v
START		:= -g

all : $(ELF) $(HEX) $(BIN) size

$(ELF) : $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

size: $(ELF)
	$(SIZE) $<

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(MCUFLAGS) -x assembler-with-cpp -MMD -MP -c $< -o $@

clean :
	$(RM) $(OBJDIR)/* $(BUILD)/*

print_vars :
	echo $(LDSCRIPT)

flash :
	$(CUBEPROG) $(CONNECT) $(PORT) $(ERASE) $(WRITE) $(ELF) $(VERIFY) $(START)

-include $(DEP)

.PHONY : clean print_vars all flash