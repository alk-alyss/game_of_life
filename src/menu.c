#include "menu.h"

int menuActive;

int menu(void){
	int mode = 0;

	SDL_Rect *buttons = calloc(MENU_BUTTONS, sizeof *buttons);
	for(int i=0; i<MENU_BUTTONS; i++){
		buttons[i].h = 50;
		buttons[i].w = 100;
		buttons[i].x = SCREEN_WIDTH/2 - buttons[i].w/2;
		buttons[i].y = SCREEN_HEIGHT/(MENU_BUTTONS+1) * (i+1) - buttons[i].h/2;
	}

	SDL_Color menuColor = {7, 143, 173, 255};

	menuActive = 1;
	while(menuActive){
		prepareScene(menuColor);
		
		mode = menuInput(buttons);

		for(int i=0; i<MENU_BUTTONS; i++){
			drawRect(buttons[i], White);
		}

		drawText("Random", menuFont, Black, buttons[0]);
		drawText("Draw", menuFont, Black, buttons[1]);
		drawText("Help", menuFont, Black, buttons[2]);

		presentScene();
		
		SDL_Delay(50);
	}

	return mode;
}