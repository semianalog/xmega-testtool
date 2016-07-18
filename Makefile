PROJECT = xmega-testtool

CSOURCES_XMEGASER = $(shell find xmegaser -name '*.c')
SSOURCES_XMEGASER = $(shell find xmegaser -name '*.s')
OBJECTS_XMEGASER = $(patsubst %.c,%.o,${CSOURCES_XMEGASER}) $(patsubst %.s,%.o,${SSOURCES_XMEGASER})

OBJECTS = main.o testtool.o esh/esh.o ${OBJECTS_XMEGASER}

CC = avr-gcc
AS = avr-as
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy
SIZE = avr-size

CFLAGS = -mmcu=atxmega128a1u -DF_CPU=32000000uLL -std=gnu11 -Wall -Wextra -Werror \
		 -O2 -g -flto -Iesh -Ixmegaser -iquote.

.PHONY:	all clean

all:	${PROJECT}.hex ${PROJECT}.disasm

%.hex: %.elf
	${OBJCOPY} -O ihex $< $@

%.disasm: %.elf
	${OBJDUMP} -S $< > $@

${PROJECT}.elf:	${OBJECTS}
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} $^
	${SIZE} $@

clean:
	rm -f ${PROJECT}.hex ${PROJECT}.elf ${PROJECT}.disasm ${OBJECTS}

