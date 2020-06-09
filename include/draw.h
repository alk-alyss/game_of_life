#ifndef DRAW_H
#define DRAW_H

#include "common.h"

void prepareScene(SDL_Color bg);
void drawRect(SDL_Rect rect, SDL_Color c);
void drawText(const char* text, TTF_Font* font, SDL_Color color, SDL_Rect rect);
void presentScene(void);

#endif