#include "input.h"

void mouseWheelEvent(Grid* grid, SDL_Event event);

void mainInput(Grid* grid){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
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
				break;

			case SDL_MOUSEWHEEL:
				mouseWheelEvent(grid, event);
				break;

			default:
				break;
		}
	}
}

Uint8 menuInput(SDL_Rect* buttons){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
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
				else if(SDL_PointInRect(&mouse, &buttons[2])){
					exit(0);
				}
				break;

			default:
				break;
		}
	}
	return 0;
}

void gridInput(Grid* grid){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			SDL_Point mouse;
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT){
					mouse.x = event.button.x;
					mouse.y = event.button.y;
					flipCell(*grid, mouse);
				}
				break;

			case SDL_MOUSEMOTION:
				if(event.motion.state == SDL_BUTTON_RMASK)
					moveGrid(-1*event.motion.xrel, -1*event.motion.yrel);
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
	if(event.wheel.y < 0 && cellSize - 2 < 0.001) return;
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	Uint64 newRows = rows;
	Uint64 newCols = cols;
	double newCellSize = cellSize + event.wheel.y * 0.05;

	if(newCellSize){
		newRows = (Uint64) (SCREEN_HEIGHT/newCellSize) + MARGIN;
		newCols = (Uint64) (SCREEN_WIDTH/newCellSize) + MARGIN;
	}

	if(newRows < rows) newRows = rows;
	if(newCols < cols) newCols = cols;

	*grid = resizeGrid(*grid, newRows, newCols);
	initState = resizeGrid(initState, newRows, newCols);

	rows = newRows;
	cols = newCols;

	double visRows = SCREEN_HEIGHT/cellSize;
	double visCols = SCREEN_WIDTH/cellSize;
	// Sint64 ratioY = (Sint64)(mouse.y)/SCREEN_HEIGHT;
	// Sint64 ratioX = (Sint64)(mouse.x)/SCREEN_WIDTH;
	double ratioX = 0.5;
	double ratioY = 0.5;
	double diffY = visRows*newCellSize - SCREEN_HEIGHT;
	double diffX = visCols*newCellSize - SCREEN_WIDTH;
	double offY = diffY * ratioY / newCellSize;
	double offX = diffX * ratioX / newCellSize;

	cellSize = newCellSize;

	// if(event.wheel.y > 0){
	// 	offX *= -1;
	// 	offY *= -1;
	// }

	moveGrid(0, 0);
}