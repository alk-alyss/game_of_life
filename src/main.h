#include "common.h"

extern void initSDL(void);
extern void cleanup(void);

extern void presentScene(void);
extern void prepareScene(void);

extern void doInput(void);

extern Cell **initGrid(void);
extern void randomStartingState(Cell **grid);
extern int getNeighbourSum(Cell **grid, int i, int j);
extern Cell **nextState(Cell **grid);
extern void drawGrid(Cell **grid);

App app;