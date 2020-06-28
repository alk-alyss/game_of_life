#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

typedef struct{
	int* b;
	int* s;
	int blen;
	int slen;
} rule_t;

typedef rule_t* Rule;

typedef bool Cell;
typedef Cell** Grid;

#endif