#include "common.h"
#include "grid.h"
#include "input.h"

void zoomGrid(Grid* grid, SDL_Event event);

void mainInput(Grid* grid){
	/*
	Simulation loop event handler
	*/
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						// ESC = exit simulation to main menu
						running = false;
						break;
					case SDLK_RETURN:
						// ENTER = pause/restart simulation
						paused = !paused;
						break;
					case SDLK_SPACE:
						// SPACE = step simulation if paused
						if(paused) *grid = nextState(*grid);
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				if(event.motion.state == SDL_BUTTON_RMASK)
					// Moving the mouse while pressing RMB moves grid view
					moveGrid(-1*event.motion.xrel, -1*event.motion.yrel);
				break;

			case SDL_MOUSEWHEEL:
				// Zoom grid with mouse wheel
				zoomGrid(grid, event);
				break;

			default:
				break;
		}
	}
}

Sint8 menuInput(SDL_Rect* buttons){
	/*
	Main menu event handler
	*/
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN: ;
				// Determine what button is pressed and return its index
				SDL_Point mouse = {event.button.x, event.button.y};
				if(SDL_PointInRect(&mouse, &buttons[0])){
					return 0;
				}
				else if(SDL_PointInRect(&mouse, &buttons[1])){
					return 1;
				}
				else if(SDL_PointInRect(&mouse, &buttons[2])){
					return 2;
				}
				else if(SDL_PointInRect(&mouse, &buttons[3])){
					return 3;
				}
				break;

			default:
				break;
		}
	}
	return -1;
}

void gridInput(Grid* grid){
	/*
	Draw screen event handler
	*/
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			SDL_Point mouse;
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN:
				// Change the state of the cell selected with the mouse
				if(event.button.button == SDL_BUTTON_LEFT){
					mouse.x = event.button.x;
					mouse.y = event.button.y;
					flipCell(*grid, mouse);
				}
				break;

			case SDL_MOUSEMOTION:
				if(event.motion.state == SDL_BUTTON_RMASK)
					// Moving the mouse while pressing RMB moves grid view
					moveGrid(-1*event.motion.xrel, -1*event.motion.yrel);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						// ENTER = start simulation
						drawing = false;
						break;
					case SDLK_c:
						// c = clear grid
						clearGrid(*grid);
						break;
					case SDLK_g:
						// g = add gosper glider gun at mouse position
						SDL_GetMouseState(&mouse.x, &mouse.y);
						addGosperGun(*grid, mouse);
						break;
					case SDLK_ESCAPE:
						// ESC = exit to main menu
						drawing = false;
						running = false;
						break;
					case SDLK_SPACE:
						// SPACE = step simulation
						drawing = false;
						paused = true;
						advance = true;
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEWHEEL:
				// Zoom grid with mouse wheel
				zoomGrid(grid, event);
				break;

			default:
				break;
		}
	}
}

void ruleInput(void){
	/*
	Rule selection event handler
	*/
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						// ESC = exit to main menu
						gettingRule = false;
						running = false;
						break;
				}
				break;
			
			default:
				break;
		}
	}
}

void zoomGrid(Grid* grid, SDL_Event event){
	/*
	Function to handle zoom
	*/
	if(event.wheel.y < 0 && cellSize - 3 < 0.001) return;
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

	// double visRows = SCREEN_HEIGHT/cellSize;
	// double visCols = SCREEN_WIDTH/cellSize;
	// // Sint64 ratioY = (Sint64)(mouse.y)/SCREEN_HEIGHT;
	// // Sint64 ratioX = (Sint64)(mouse.x)/SCREEN_WIDTH;
	// double ratioX = 0.5;
	// double ratioY = 0.5;
	// double diffY = visRows*newCellSize - SCREEN_HEIGHT;
	// double diffX = visCols*newCellSize - SCREEN_WIDTH;
	// double offY = diffY * ratioY / newCellSize;
	// double offX = diffX * ratioX / newCellSize;

	cellSize = newCellSize;

	// if(event.wheel.y > 0){
	// 	offX *= -1;
	// 	offY *= -1;
	// }

	moveGrid(0, 0);
}