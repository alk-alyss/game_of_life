#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

typedef struct{
	unsigned short int r;
	unsigned short int g;
	unsigned short int b;
	unsigned short int a;
} Color;

typedef struct{
	SDL_Rect rect;
	int alive;
} Cell;

#endif