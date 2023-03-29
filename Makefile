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

# bin folder
BIN_DIR := bin
# define the C source files
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# define the C object files 
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(BIN_DIR)/main
	@echo "✅ Build complete 🥳"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c clean create-build-dir create-bin-dir
	@$(CC) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@$(CC) -c $< -o $@

create-build-dir:
	@mkdir build
	@echo "✅ Created build directory"

create-bin-dir:
	@mkdir bin
	@echo "✅ Created bin directory"

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✅ Cleaned build and bin directories 🗑️"

run:
	@echo "🚀 executing main program"
	@./bin/main

run-manual:
	@echo "🚀 executing main program"
	@./bin/main --manual-scoring

run-input:
	@echo "🚀 executing program with"
	@./bin/main -i ./assets/input.txt

run-bin:
	@echo "🚀 executing program with"
	@./bin/main --output ./results/end.csv

doxygen:
	@doxygen
	@echo "✅ Documentation generated 📚"