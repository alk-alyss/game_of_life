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

extern TTF_Font *menuFont;

extern int running;
extern int menuActive;
extern int drawing;

extern SDL_Color White;
extern SDL_Color Black;

#endif