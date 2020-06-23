# Program and Path definitions
PROG := game_of_life
BIN	:= bin
SRC	:= src
INCLUDE	:= include
LIBS	:= lib
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

# Compiler options
CC := gcc
WFLAGS := -Wall -Wstrict-prototypes -Wmissing-prototypes

CINCLUDES := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBSFLAG  := $(patsubst %,-L%, $(LIBS:%/=%))

CFLAGS  += -std=c99 ${WFLAGS} 
CXXFLAGS += $(CINCLUDES)

# Linker options
LDFLAGS += $(LIBSFLAG) -lSDL2 -lSDL2_ttf -lm -Wl,-rpath='$$ORIGIN/../../lib'

# Source and Object definitions
SRCS := $(wildcard $(patsubst %,%/*.c, $(SRCDIRS)))
OBJS := $(patsubst $(SRC)/%.c, %.o, $(SRCS))

# Debug build settings
DBGDIR := $(BIN)/debug
DBGEXE := $(DBGDIR)/$(EXE)
DBGOBJDIR := $(DBGDIR)/obj
DBGOBJS := $(addprefix $(DBGOBJDIR)/, $(OBJS))
DBGCFLAGS := -g3 -O0

# Release build settings
RELDIR := $(BIN)/release
RELEXE := $(RELDIR)/$(EXE)
RELOBJDIR := $(RELDIR)/obj
RELOBJS := $(addprefix $(RELOBJDIR)/, $(OBJS))
RELCFLAGS := -O3

.PHONY: all clean debug release remake

# Default build
all: release

# Debug rules
debug: $(DBGEXE)
	@cp $(SRC)/arial.ttf $(DBGDIR)/arial.ttf

$(DBGEXE): $(DBGOBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DBGOBJDIR)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(DBGOBJDIR)
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $(DBGCFLAGS) -o $@ $<

# Release rules
release: $(RELEXE)
	@cp $(SRC)/arial.ttf $(RELDIR)/arial.ttf

$(RELEXE): $(RELOBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(RELOBJDIR)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(RELOBJDIR)
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $(RELCFLAGS) -o $@ $<

# Clean and build
remake: clean all

# Clean build files
clean:
	$(RM) -r $(BIN)
