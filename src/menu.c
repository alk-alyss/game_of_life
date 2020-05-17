#include "menu.h"

void menu(void){
	int menuActive = 1;
	
	SDL_Rect *buttons = calloc(MENU_BUTTONS, sizeof *buttons);
	for(int i=0; i<MENU_BUTTONS; i++){
		buttons[i].h = 50;
		buttons[i].w = 100;
		buttons[i].x = SCREEN_WIDTH/2 - buttons[i].w/2;
		buttons[i].y = SCREEN_HEIGHT/2 - buttons[i].h/2;
	}

	while(menuActive){
		prepareScene(Black);
		
		menuInput(buttons);

		for(int i=0; i<MENU_BUTTONS; i++){
			drawRect(buttons[i], White);
		}
		
		presentScene();
		
		SDL_Delay(50);

	}
}