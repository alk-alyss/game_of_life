#include "draw.h"

SDL_Color White = {255, 255, 255 ,255};
SDL_Color Black = {0, 0, 0 ,255};

void prepareScene(SDL_Color bg){
	SDL_SetRenderDrawColor(app.renderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderClear(app.renderer);
}

void drawRect(SDL_Rect rect, SDL_Color c){
	SDL_SetRenderDrawColor(app.renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(app.renderer, &rect);
}

void presentScene(void){
	SDL_RenderPresent(app.renderer);
}
