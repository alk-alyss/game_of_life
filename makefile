# Program and Path definitions
PROG := game_of_life
BIN	:= bin
SRC	:= src
INCLUDE	:= include
DEPS := defs.h common.h structs.h

ifeq ($(OS),Windows_NT)
EXECUTABLE := $(PROG).exe
SOURCEDIRS := $(SRC)
INCLUDEDIRS := $(INCLUDE)
else
EXECUTABLE := $(PROG)
SOURCEDIRS := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
endif

vpath %.c $(SOURCEDIRS)
vpath %.h $(INCLUDEDIRS)
vpath %.o $(BIN)

# RM definition
RM := rm -rf

# Compiler options
CC := gcc
SFLAGS := -std=c99
GFLAGS := -g
OFLAGS := -O0
WFLAGS := -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes

CINCLUDES := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

CFLAGS  += ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} 
CXXFLAGS += `sdl2-config --cflags` $(CINCLUDES)

# Linker options
LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Source and Object definitions
SOURCES	:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS	:= $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(SOURCES))

# Top-level rule to create the program
all: $(EXECUTABLE)

# Linking the program
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling source files
$(BIN)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

# Run the program
run: all
	@./$(EXECUTABLE)

# Cleaning everything that can be automatically recreated with "make"
.PHONY: clean
clean:
	-$(RM) $(OBJECTS) $(EXECUTABLE)