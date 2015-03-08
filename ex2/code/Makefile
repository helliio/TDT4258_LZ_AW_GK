# Example Makefile
#
# Exercise 2, TDT4258

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall -Isrc/include
LDFLAGS=--specs=nosys.specs -mcpu=cortex-m3 -mthumb -g -lgcc -lc -lefm32gg -Llib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g
LINKERSCRIPT=lib/efm32gg.ld


SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=obj/%.o)


ex2.bin: ex2.elf
	${OBJCOPY} -O binary $< $@

ex2.elf: $(OBJECTS)
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS}

$(OBJECTS): obj/%.o: src/%.c
	${CC} ${CFLAGS} -c $< -o $@


.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r

.PHONY : clean
clean :
	-rm -r obj/* ex2.bin ex2.elf
