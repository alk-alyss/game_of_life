#include "input.h"

Uint32 newRows, newCols;

void mouseWheelEvent(Grid* grid, SDL_Event event);

void mainInput(Grid *grid){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						running = false;
						break;
					case SDLK_RETURN:
						paused = !paused;
						break;
					case SDLK_SPACE:
						if(paused) *grid = nextState(*grid);
						break;
					default:
						break;
				}

			case SDL_MOUSEWHEEL:
				mouseWheelEvent(grid, event);
				break;

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
					menuActive = false;
					return 0;
				}
				else if(SDL_PointInRect(&mouse, &buttons[1])){
					menuActive = false;
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

void gridInput(Grid *grid){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch (event.type){
			SDL_Point mouse;
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse.x = event.button.x;
				mouse.y = event.button.y;
				flipState(*grid, mouse);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						drawing = false;
						break;
					case SDLK_c:
						clearGrid(*grid);
						break;
					case SDLK_g:
						SDL_GetMouseState(&mouse.x, &mouse.y);
						addGosperGun(*grid, mouse);
						break;
					case SDLK_ESCAPE:
						drawing = false;
						running = false;
						break;
					case SDLK_SPACE:
						drawing = false;
						paused = true;
						advance = true;
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEWHEEL:
				mouseWheelEvent(grid, event);
				break;

			default:
				break;
		}
	}
}

void mouseWheelEvent(Grid* grid, SDL_Event event){
	SDL_Point mouse;
	if(event.wheel.y < 0 && cellSize - 2 < 0.001) return;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	newRows = rows;
	newCols = cols;
	cellSize += event.wheel.y * 0.1;

	if(cellSize){
		newRows = (Uint32) (SCREEN_HEIGHT/cellSize);
		newCols = (Uint32) (SCREEN_WIDTH/cellSize);
	}

	if(newRows < rows) newRows = rows;
	if(newCols < cols) newCols = cols;

	*grid = resizeGrid(*grid, newRows, newCols);
	// moveGrid(*grid, mouse);
	initState = resizeGrid(initState, newRows, newCols);

	rows = newRows;
	cols = newCols;
}