#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

typedef struct{
	SDL_Rect rect;
	bool alive;
} Cell;
typedef Cell **Grid;

typedef struct{
	Grid grid;
	Uint32 rows;
	Uint32 cols;
} metaGrid;

#endif