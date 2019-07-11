#upload to board
AVRDUDE=avrdude -F -V

#create object file
OBJCOPY=avr-objcopy 

#compiler
CC=avr-gcc 

#make clean
RM=rm -f

#PARAMETERS
MCU=atmega328p
F_CPU=16000000UL
BIN_FORMAT=ihex
PORT=/dev/ttyACM0
BAUD=115200
PROTOCOL=arduino
PART=ATMEGA328P
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
PROG=spaceship_interface

.SUFFIXES: .elf .hex

.c.elf:
	$(CC) $(CFLAGS) -o $@ $<

.elf.hex:
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

.PHONY: all
all: ${PROG}.hex

${PROG}.hex: ${PROG}.elf

${PROG}.elf: ${PROG}.c

.PHONY: clean
clean:
	$(RM) ${PROG}.elf ${PROG}.hex

.PHONY: upload
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) \
			-b $(BAUD) -U flash:w:${PROG}.hex
