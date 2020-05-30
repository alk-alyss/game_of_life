#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "grid.h"

void mainInput(void);
Uint8 menuInput(SDL_Rect *buttons);
void gridInput(Cell **grid);

#endif