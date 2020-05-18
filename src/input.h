#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "grid.h"

void mainInput(void);
int menuInput(SDL_Rect *buttons);
void gridInput(Cell **grid);

#endif