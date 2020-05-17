#include "draw.h"

Color white = {255, 255, 255 ,255};
Color black = {0, 0, 0 ,255};

void prepareScene(void){
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void drawRect(SDL_Rect rect, Color c){
	SDL_SetRenderDrawColor(app.renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(app.renderer, &rect);
}

void presentScene(void){
	SDL_RenderPresent(app.renderer);
}
