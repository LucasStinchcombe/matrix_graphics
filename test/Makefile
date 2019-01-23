# Makefile for matrix graphics tests

LDFLAGS= $(shell pkg-config --cflags --libs check)
CFLAGS= -I..
CC=gcc

SOURCES:= matrix.c vector.c
TEST_SOURCES:=$(wildcard *.t.c)

BUILD=./build
DEPS=./deps

info:
	@echo CC:$(CC)
	@echo SOURCES:$(SOURCES)
	@echo CFLAGS:$(CFLAGS)
	@echo LDFLAGS:$(LDFLAGS)
	@echo TEST_SOURCES:$(TEST_SOURCES)

test: $(TEST_SOURCES:%.t.c=$(BUILD)/%)
	for runner in $(TEST_SOURCES:%.t.c=$(BUILD)/%); do \
		$$runner; \
	done

$(BUILD)/%: $(BUILD)/%.t.o $(SOURCES:%.c=$(BUILD)/%.o)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(BUILD)/%.o: | build_dir
	$(CC) $(CFLAGS) -c -o $@ $<

# Compiler-generated dependencies
$(DEPS)/%.d: %.c
	@echo generating deps for $@
	@set -e; rm -f $@; \
	mkdir -p $(DEPS); \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.c:: ../%.c
	cp $< .

build_dir:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
	rm -rf $(DEPS)
	rm -rf $(SOURCES)

-include $(SOURCES:%.c=$(DEPS)/%.d)
-include $(TEST_SOURCES:%.c=$(DEPS)/%.d)
