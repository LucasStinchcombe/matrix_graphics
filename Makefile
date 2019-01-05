# Makefile for power test
#

BUILD=./build
GCC=avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -Os

build_dir:
	mkdir -p $(BUILD)

$(BUILD)/main.o: main.c spi.h | build_dir
	$(GCC) -c -o $@ $<

$(BUILD)/spi.o: spi.c spi.h | build_dir
	$(GCC) -c -o $@ $<

$(BUILD)/conway.o: conway.c conway.h | build_dir
	$(GCC) -c -o $@ $<

$(BUILD)/main: $(BUILD)/main.o $(BUILD)/spi.o $(BUILD)/conway.o
	avr-gcc -mmcu=atmega328p $^ -o $@

$(BUILD)/main.hex: $(BUILD)/main
	avr-objcopy -O ihex -R .eeprom $^ $@

dfu: $(BUILD)/main.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P \
			/dev/ttyACM0 -b 115200 -U flash:w:$^
clean:
	rm -rf $(BUILD)
