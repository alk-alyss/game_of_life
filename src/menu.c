#include "common.h"
#include "draw.h"
#include "input.h"
#include "menu.h"

bool menuActive;

Sint8 menu(void){
	/*
	Main menu
	*/
	Sint8 mode = 0;

	// Button rectangles
	SDL_Rect* buttons = calloc(MENU_BUTTONS, sizeof *buttons);
	for(Uint8 i=0; i<MENU_BUTTONS; i++){
		buttons[i].h = 50;
		buttons[i].w = 100;
		buttons[i].x = SCREEN_WIDTH/2 - buttons[i].w/2;
		buttons[i].y = SCREEN_HEIGHT/(MENU_BUTTONS+1) * (i+1) - buttons[i].h/2;
	}

	// SDL_Color menuColor = {7, 143, 173, 255};
	SDL_Color menuColor = Black;

	// Main menu loop
	menuActive = true;
	while(menuActive){
		prepareScene(menuColor);
		
		for(Uint8 i=0; i<MENU_BUTTONS; i++){
			drawRect(buttons[i], White);
		}

		// Draw button labels
		drawText("Random", menuFont, Black, buttons[0]);
		drawText("Draw", menuFont, Black, buttons[1]);
		drawText("Quit", menuFont, Black, buttons[2]);

		mode = menuInput(buttons);
		if(mode != -1) menuActive = false;

		presentScene();
		
		SDL_Delay(50);
	}

	// Free resources and return mode
	free(buttons);
	return mode;
}