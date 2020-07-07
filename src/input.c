#include "common.h"
#include "grid.h"
#include "input.h"

void zoomGrid(Grid* grid, SDL_Event event);
int compChars(const void* a, const void* b);

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

			case SDL_MOUSEBUTTONDOWN:;
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
					case SDLK_r:
						randomStartingState(*grid);
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

Sint8 ruleInput(SDL_Rect* buttons, SDL_Rect* inputs, char** bs){
	/*
	Rule selection event handler
	*/
	SDL_Event event;
	static Sint8 activeInput = -1;
	Sint8 result = -1;
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE){
					gettingRule = false;
					running = false;
				}
				if(activeInput > -1){
					Uint64 keycode = event.key.keysym.sym;
					Uint64 length;
					// Delete all numbers in active input field
					if(keycode == SDLK_DELETE){
						bs[activeInput] = realloc(bs[activeInput], sizeof (char));
						bs[activeInput][0] = '\0';
						return result;
					}
					// Delete last number in active input field
					else if(keycode == SDLK_BACKSPACE){
						length = strlen(bs[activeInput]);
						if(length == 0) return result;
						bs[activeInput] = realloc(bs[activeInput], length * sizeof (char));
						bs[activeInput][length-1] = '\0';
						return result;
					}
					// Convert keypad number codes to ASCII
					else if(keycode-(1<<30) >= 89 && keycode-(1<<30) <= 98){
						keycode -= 0x40000059;
						keycode = keycode == 9 ? 0 : keycode + 1;
						keycode += 48;
					}
					// Ignore all keys except numbers
					else if(keycode < 48 || keycode > 57){
						return result;
					}

					length = strlen(bs[activeInput]);

					// Check that the key pressed is not already stored
					for(Uint64 i=0; i<length; i++){
						if(keycode == bs[activeInput][i]) return result;
					}

					// Append character to string and sort characters
					// bs[activeInput] = realloc(bs[activeInput], length+1);
					bs[activeInput][length] = (char) keycode;
					qsort(bs[activeInput], length+1, sizeof(char), compChars);
					bs[activeInput] = realloc(bs[activeInput], (length+2) * sizeof (char));
					bs[activeInput][length+1] = '\0';
				}

				break;


			case SDL_MOUSEBUTTONDOWN:;
				// Determine what button/input is selected and return its index
				SDL_Point mouse = {event.button.x, event.button.y};
				if(SDL_PointInRect(&mouse, &buttons[0])){
					activeInput = -1;
					strcpy(bs[0], "3");
					strcpy(bs[1], "23");
					result = 0;
				}
				else if(SDL_PointInRect(&mouse, &buttons[1])){
					activeInput = -1;
					strcpy(bs[0], "36");
					strcpy(bs[1], "23");
					result = 1;
				}
				else if(SDL_PointInRect(&mouse, &buttons[2])){
					activeInput = -1;
					strcpy(bs[0], "2");
					strcpy(bs[1], "");
					result = 2;
				}
				else if(SDL_PointInRect(&mouse, &buttons[3])){
					activeInput = -1;
					strcpy(bs[0], "1357");
					strcpy(bs[1], "1357");
					result = 3;
				}
				else if(SDL_PointInRect(&mouse, &inputs[0])){
					activeInput = 0;
					result = 4;
				}
				else if(SDL_PointInRect(&mouse, &inputs[1])){
					activeInput = 1;
					result = 5;
				}
				break;			
			
			default:
				break;
		}
	}
	return result;
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

int compChars(const void* a, const void* b){
	return (*(char*)a - *(char*)b);
}