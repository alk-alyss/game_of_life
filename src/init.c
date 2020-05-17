#include "init.h"

TTF_Font *menuFont;

void initSDL(void){
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	
	windowFlags = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	
	if(!app.window){
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
	
	if(!app.renderer){
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	if(TTF_Init() == -1){
		printf("Failed to initialize ttf: %s", TTF_GetError());
		exit(2);
	}

	menuFont = TTF_OpenFont("arial.ttf", 25);

	if(menuFont == NULL) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(2);
	}
}

void cleanup(void){
	TTF_CloseFont(menuFont);

	SDL_DestroyRenderer(app.renderer);
	
	SDL_DestroyWindow(app.window);

	TTF_Quit();
	
	SDL_Quit();
}
