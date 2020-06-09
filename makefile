# Program and Path definitions
PROG := game_of_life
BIN	:= bin
SRC	:= src
INCLUDE	:= include
DEPS := defs.h common.h structs.h

ifeq ($(OS),Windows_NT)
EXE := $(PROG).exe
SRCDIRS := $(SRC)
INCLUDEDIRS := $(INCLUDE)
else
EXE := $(PROG)
SRCDIRS := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
endif

vpath %.c $(SRCDIRS)
vpath %.h $(INCLUDEDIRS)
vpath %.o $(BIN)

# Compiler options
CC := gcc
WFLAGS := -Wall -Wstrict-prototypes -Wmissing-prototypes

CINCLUDES := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

CFLAGS  += -std=c99 ${WFLAGS} 
CXXFLAGS += `sdl2-config --cflags` $(CINCLUDES)

# Linker options
LDFLAGS += `sdl2-config --libs` -lSDL2_ttf -lm

# Source and Object definitions
SRCS := $(wildcard $(patsubst %,%/*.c, $(SRCDIRS)))
OBJS := $(patsubst $(SRC)/%.c, %.o, $(SRCS))

# Debug build settings
DBGDIR := $(BIN)/debug
DBGEXE := $(DBGDIR)/$(EXE)
DBGOBJS := $(addprefix $(DBGDIR)/, $(OBJS))
DBGCFLAGS := -g3 -Og

# Release build settings
RELDIR := $(BIN)/release
RELEXE := $(RELDIR)/$(EXE)
RELOBJS := $(addprefix $(RELDIR)/, $(OBJS))
RELCFLAGS := -O3

.PHONY: all clean debug release remake

# Default build
all: debug

# Debug rules
debug: $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DBGDIR)/%.o: %.c
	@mkdir -p $(DBGDIR)
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $(DBGCFLAGS) -o $@ $<

# Release rules
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(RELDIR)/%.o: %.c
	@mkdir -p $(RELDIR)
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $(RELCFLAGS) -o $@ $<

# Clean and build
remake: clean all

# Clean build files
clean:
	$(RM) -r $(BIN)