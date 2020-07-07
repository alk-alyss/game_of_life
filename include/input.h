#ifndef INPUT_H
#define INPUT_H

void mainInput(Grid* grid);
Sint8 menuInput(SDL_Rect* buttons);
void gridInput(Grid* grid);
Sint8 ruleInput(SDL_Rect* buttons, SDL_Rect* inputs, char** string);

#endif