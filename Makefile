# File needed to compile simply the programm
#
# @authors Alice MABILLE, Benjamin PAUMARD
# @version 1.0.0
# @since January 25, 2023

# defining constants
# compiler
CC = gcc

# source folder
SRC_DIR := src

# binary build
BUILD_DIR := build

# output folder
OUTPUT_DIR := output

# define flags to be used
CFLAGS	:= `pkg-config --cflags gtk+-3.0`

LFLAGS := `pkg-config --libs gtk+-3.0`

# define the C source files
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# define the C object files 
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT_DIR)/main $(LFLAGS)
	@echo "✅ Build complete 🥳"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c clean create-build-dir create-output-dir
	@$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

create-build-dir:
	@mkdir build
	@echo "✅ Created build directory"

create-output-dir:
	@mkdir output
	@echo "✅ Created output directory"

clean:
	@rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "✅ Cleaned build and output directories 🗑️"

run:
	@echo "🚀 executing main programm"
	@./output/main

run-gui:
	@echo "🚀 executing GUI version"
	@./output/main --graphical

run-cli:
	@echo "🚀 executing CLI version"
	@./output/main -i ./assets/input.txt


doxygen:
	@doxygen
	@echo "✅ Documentation generated 📚"