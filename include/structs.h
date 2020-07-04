#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

typedef bool Cell;
typedef Cell** Grid;

#endif