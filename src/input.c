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
	SDL_Point mouse;
	if(event.wheel.y < 0 && cellSize - 2 < 0.001) return;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	Uint32 newRows = rows;
	Uint32 newCols = cols;
	double newCellSize = cellSize + event.wheel.y * 0.1;

	if(newCellSize){
		newRows = (Uint32) (SCREEN_HEIGHT/newCellSize);
		newCols = (Uint32) (SCREEN_WIDTH/newCellSize);
	}

	if(newRows < rows) newRows = rows;
	if(newCols < cols) newCols = cols;

	*grid = resizeGrid(*grid, newRows, newCols);

	double visRows = SCREEN_HEIGHT/cellSize;
	double visCols = SCREEN_WIDTH/cellSize;
	double ratioY = (double)(mouse.y)/SCREEN_HEIGHT;
	double ratioX = (double)(mouse.x)/SCREEN_WIDTH;
	double diffY = visRows*newCellSize - SCREEN_HEIGHT;
	double diffX = visCols*newCellSize - SCREEN_WIDTH;
	Sint32 offY = diffY * ratioY;
	Sint32 offX = diffX * ratioX;

	// if(event.wheel.y > 0){
	// 	offX *= -1;
	// 	offY *= -1;
	// }

	moveGrid(offX, offY);

	initState = resizeGrid(initState, newRows, newCols);

	rows = newRows;
	cols = newCols;
	cellSize = newCellSize;
}