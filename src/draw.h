#ifndef DRAW_H
#define DRAW_H

#include "common.h"

void prepareScene(SDL_Color);
void drawRect(SDL_Rect rect, SDL_Color c);
void presentScene(void);

#endif