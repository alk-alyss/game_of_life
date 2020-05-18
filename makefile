CC = gcc

# Compiler options
SFLAGS  = -std=c99
GFLAGS  = -g
OFLAGS  = -O0
WFLAGS  = -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes

CFLAGS  += ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS}
CXXFLAGS += `sdl2-config --cflags` -lefence

# Linker options
LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Program name/ binary path/ source path
PROG = game_of_life
OUT = bin
SEARCHPATH = src

vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

# Header file dependencies
DEPS = defs.h structs.h common.h

# Required objects
FILES = draw.c init.c input.c grid.c main.c menu.c
OBJS = $(patsubst %,$(OUT)/%,$(FILES:.c=.o))

# Top-level rule to create the program.
all: $(PROG)

# Linking the program.
$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compiling source files.
$(OUT)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

# Cleaning everything that can be automatically recreated with "make".
clean:
	rm -rf $(OUT) $(PROG)