#include "common.h"
#include "draw.h"

SDL_Color White = {255, 255, 255 ,255};
SDL_Color Black = {0, 0, 0 ,255};

void prepareScene(SDL_Color bg){
	/*
	Clear screen and set background color
	*/
	SDL_SetRenderDrawColor(app.renderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderClear(app.renderer);
}

void drawRect(SDL_Rect rect, SDL_Color c){
	/*
	Fill the area defined by rect with color c
	*/
	SDL_SetRenderDrawColor(app.renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(app.renderer, &rect);
}

void drawOutline(SDL_Rect rect, SDL_Color c){
	/*
	Draw an outline around the area defined by rect with color c
	*/
	int offset = 20;
	rect.w += offset;
	rect.h += offset;
	rect.x -= offset/2;
	rect.y -= offset/2;
	SDL_SetRenderDrawColor(app.renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawRect(app.renderer, &rect);
}

void drawText(const char* text, TTF_Font* font, SDL_Color color, SDL_Rect rect){
	/*
	Render the text with color on a new surface, create a texture from the surface
	and render to the screen at the area defined by rect
	*/
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
	SDL_Rect distrect = {rect.x + rect.w/2, rect.y + rect.h/2, 4*rect.w/5, 4*rect.h/5};
	distrect.x -= distrect.w/2;
	distrect.y -= distrect.h/2;
	SDL_RenderCopy(app.renderer, texture, NULL, &distrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void presentScene(void){
	/*
	Present textures in renderer buffer to the screen
	NOTE: previous functions in this file where rendering/drawing are referenced
		imply copying the textures to the renderer buffer to be presented 
	*/
	SDL_RenderPresent(app.renderer);
}