#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#include "time.h"
#include "stdbool.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "defs.h"
#include "structs.h"

extern App app;

extern SDL_DisplayMode dm;

extern bool running, menuActive, drawing, paused, advance;

extern Uint32 rows, cols;

extern double cellSize;

extern TTF_Font* menuFont;

extern SDL_Color White, Black;

extern Grid initState;

#endif