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

void drawText(const char* text, TTF_Font* font, SDL_Color color, SDL_Rect rect){
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
	SDL_Rect distrect = {rect.x + rect.w/2, rect.y + rect.h/2, 4*rect.w/5, 4*rect.h/5};
	// SDL_QueryTexture(texture, NULL, NULL, &(distrect.w), &(distrect.h));
	distrect.x -= distrect.w/2;
	distrect.y -= distrect.h/2;
	SDL_RenderCopy(app.renderer, texture, NULL, &distrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void presentScene(void){
	SDL_RenderPresent(app.renderer);
}