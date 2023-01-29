# File needed to compile simply the programm
#
# @authors Alice MABILLE, Benjamin PAUMARD
# @version 1.0.0
# @since January 25, 2023

# defining constants
# compiler
CC = gcc

# source folder
SRC := src

# output folder
OUTPUT := output

# define flags to be used
CFLAGS	:= `pkg-config --cflags gtk+-3.0`

LFLAGS := `pkg-config --libs gtk+-3.0`

# define the C source files
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# define the C object files 
OBJECTS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SOURCES:.c=.o))

all: $(MAIN)
	@echo Executing 'all' complete!
	@echo $(SOURCES)

$(MAIN): $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!