# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.


GTEST_DIR = ./dep/googletest
TESTS_DIR := ./tests
SRC_DIR := ./src
BUILD_DIR := ./build

include dep/googletest/make/Makefile

CFLAGS=-c -Wall -g
LDFLAGS=

SODIUM_CFLAGS=`pkg-config --cflags libsodium`
SODIUM_LDFLAGS=`pkg-config --libs libsodium`
CFLAGS+=$(SODIUM_CFLAGS)
LDFLAGS+=$(SODIUM_LDFLAGS)


AT2_CFLAGS=`pkg-config --cflags argtable2`
AT2_LDFLAGS=`pkg-config --libs argtable2`
CFLAGS+=$(AT2_CFLAGS)
LDFLAGS+=$(AT2_LDFLAGS)

PANGO_CFLAGS=`pkg-config --cflags pangocairo`
PANGO_LDFLAGS=`pkg-config --libs pangocairo`
CFLAGS+=$(PANGO_CFLAGS)
LDFLAGS+=$(PANGO_LDFLAGS)

PANGOFT2_CFLAGS=`pkg-config --cflags pangoft2`
PANGOFT2_LDFLAGS=`pkg-config --libs pangoft2`
CFLAGS+=$(PANGOFT2_CFLAGS)
LDFLAGS+=$(PANGOFT2_LDFLAGS)

FC_CFLAGS=`pkg-config --cflags fontconfig`
FC_LDFLAGS=`pkg-config --libs fontconfig`
CFLAGS+=$(FC_CFLAGS)
LDFLAGS+=$(FC_LDFLAGS)


#CAIRO_CFLAGS=`pkg-config --cflags cairo`
#CAIRO_LDFLAGS=`pkg-config --libs cairo`
#CFLAGS+=$(CAIRO_CFLAGS)
#LDFLAGS+=$(CAIRO_LDFLAGS)


OBJECTS =

.PHONY: all
all: $(BUILD_DIR)/harness $(BUILD_DIR)/all-tests $(BUILD_DIR)/fonts.conf

$(BUILD_DIR)/fonts.conf:
	cp -f src/fonts.conf $(BUILD_DIR)/fonts.conf
	cp -R fonts $(BUILD_DIR)/fonts

$(BUILD_DIR)/harness: $(OBJECTS) $(BUILD_DIR)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS): $(BUILD_DIR)/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*


.PHONY: run-tests
run-tests: $(BUILD_DIR)/all-tests
	build/all-tests

include tests/Makefile
