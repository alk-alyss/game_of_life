#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "defs.h"
#include "structs.h"

extern App app;

extern SDL_DisplayMode dm;

extern Uint8 cellSize, running, menuActive, drawing;

extern Uint32 rows, cols;

extern TTF_Font *menuFont;

extern SDL_Color White, Black;

#endif