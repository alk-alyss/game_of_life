#include "common.h"

extern void initSDL(void);
extern void cleanup(void);

extern void presentScene(void);
extern void drawRect(SDL_Rect rect, Color c);
extern void prepareScene(void);

extern void doInput(void);

Cell **initGrid(void);
int getNeighbourSum(Cell **grid, int i, int j);

App app;

Color white = {255, 255, 255, 255};
Color black = {0, 0, 0, 255};