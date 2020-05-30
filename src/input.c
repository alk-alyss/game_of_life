#include "input.h"

void mainInput(void){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						running = 0;
						break;
					default:
						break;
				}

			default:
				break;
		}
	}
}

Uint8 menuInput(SDL_Rect *buttons){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN: ;
				SDL_Point mouse = {event.button.x, event.button.y};
				if(SDL_PointInRect(&mouse, &buttons[0])){
					menuActive = 0;
					return 0;
				}
				else if(SDL_PointInRect(&mouse, &buttons[1])){
					menuActive = 0;
					return 1;
				}
				else if(SDL_PointInRect(&mouse, &buttons[3])){
					exit(0);
				}
				break;

			default:
				break;
		}
	}
	return 0;
}

void gridInput(Cell **grid){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN: ;
				SDL_Point mouse = screenToGrid(event.button.x, event.button.y);
				grid[mouse.y][mouse.x].alive = !grid[mouse.y][mouse.x].alive;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						drawing = 0;
						break;
					case SDLK_c:
						for(Uint32 i=0; i<rows; i++){
							for(Uint32 j=0; j<cols; j++){
								grid[i][j].alive = 0;
							}
						}
						break;
					case SDLK_g:
						addGosperGun(grid);
					default:
						break;
				}

			default:
				break;
		}
	}
}