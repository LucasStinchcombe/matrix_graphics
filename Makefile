# Makefile for 16x16 led matrix driver

CFLAGS= -DF_CPU=16000000UL -mmcu=atmega328p -Os
CC=avr-gcc
FORMAT=clang-format
FORMAT_STYLE=file

BUILD=./build
DEPS=./deps
TMP=./tmp

.PHONY: build \
		dfu \
		info \
		format \
		clean

SOURCES:=$(wildcard *.c)

# PHONIES

build: $(BUILD)/main | build_dir

dfu: $(BUILD)/main.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P \
			/dev/ttyACM0 -b 115200 -U flash:w:$^

info:
	@echo CC:$(CC)
	@echo SOURCES:$(SOURCES)
	@echo CFLAGS:$(CFLAGS)

format:
	@mkdir -p $(TMP); \
	for src in $(SOURCES) $(wildcard *.h); do \
		$(FORMAT) -style=$(FORMAT_STYLE) $$src > $(TMP)/$$src; \
		mv $(TMP)/$$src $$src; \
	done
	rmdir $(TMP)
	@echo "Done"

clean:
	rm -rf $(BUILD)
	rm -rf $(DEPS)
	rm -rf $(TMP)

# Compiler-generated dependencies
$(DEPS)/%.d: %.c
	@echo generating deps for $@
	@set -e; rm -f $@; \
	mkdir -p $(DEPS); \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SOURCES:%.c=$(DEPS)/%.d)

# Generic .o file compilation
$(BUILD)/%.o: | build_dir
	$(CC) $(CFLAGS) -c -o $@ $<

# Creat BUILD directory
build_dir:
	mkdir -p $(BUILD)

# Main executable depends on all .o files
$(BUILD)/main: $(SOURCES:%.c=$(BUILD)/%.o)
	$(CC) $(CFLAGS) $^ -o $@

# Generic hexfile from avr executable
$(BUILD)/%.hex: $(BUILD)/%
	avr-objcopy -O ihex -R .eeprom $^ $@

