CC = arm-none-eabi-gcc
MACH = cortex-m4


# NEW "PARANOID" SAFETY FLAGS:
# -Werror             : Warnings = Errors (Code won't build if it's messy)
# -Wstrict-prototypes : Prevents bad function calls
# -fstack-usage       : Generates .su files to check RAM usage
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -Wextra -Werror -Wstrict-prototypes -fstack-usage -O0

LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32f446re.ld -Wl,-Map=final.map -nostartfiles

# Define where source files are
SRC_DIR = src

all: main.elf

main.elf: main.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^

# Updated rule: Look for main.c inside src/
main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -o $@ $^

# Updated rule: Look for startup.c inside src/
startup.o: $(SRC_DIR)/startup.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.map *.su