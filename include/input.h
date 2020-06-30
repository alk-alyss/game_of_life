#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "grid.h"

void mainInput(Grid* grid);
Sint8 menuInput(SDL_Rect* buttons);
void gridInput(Grid* grid);
void ruleInput(void);

#endif