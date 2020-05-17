#include "main.h"

App app;

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);

	menu();

	Cell **grid = initGrid();

	randomStartingState(grid);

	while(1){
		prepareScene(Black);
		
		mainInput();

		grid = nextState(grid);

		drawGrid(grid);
		
		presentScene();
		
		SDL_Delay(50);
	}

	return 0;
}