.PHONY: clean tidy all test

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=gnu99 -Iheader -g
LFLAGS = -lm

# Directories
BUILD_DIR = ./build/
SRC_DIR = ./src/
HEADER_DIR = ./header/

# Source and header files
HDR = $(wildcard $(HEADER_DIR)*.h)
SRC = $(filter-out $(SRC_DIR)*_test.c, $(wildcard $(SRC_DIR)*.c))
OBJ = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC))

# Test flags and files
CFLAGS_TEST = $(CFLAGS)
LFLAGS_TEST = $(LFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
SRC_TEST = $(wildcard $(SRC_DIR)*_test.c)
OBJ_TEST = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC_TEST))

# Default target
all: main

# Main executable
main: $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)tree $(OBJ) $(LFLAGS)
	@echo "Build complete. Executable is at $(BUILD_DIR)tree"

# Test executable
test: $(OBJ_TEST)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS_TEST) -o $(BUILD_DIR)test $(OBJ_TEST) $(LFLAGS_TEST)
	@echo "Test build complete. Executable is at $(BUILD_DIR)test"

# Rule for building object files
$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(HDR)
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<
	@echo "Compiled $< -> $@"

# Clean up all generated files
clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned up build directory."

# Tidy intermediate object files
tidy:
	rm -rf $(BUILD_DIR)*.o
	@echo "Removed intermediate object files."
