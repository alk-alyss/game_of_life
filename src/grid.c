#include "grid.h"

bool drawing, gettingRule;
double gridOffX = 200;
double gridOffY = 200;
Rule rule;

Grid initGrid(Uint64 _rows, Uint64 _cols){
	Grid grid = calloc(_rows, sizeof *grid);
	for(Uint64 i=0; i<_rows; i++){
		grid[i] = calloc(_cols, sizeof **grid);
		for(Uint64 j=0; j<_cols; j++){
			grid[i][j] = false;
		}
	}
	return grid;
}

Grid resizeGrid(Grid grid, Uint64 _rows, Uint64 _cols){
	Grid newGrid = initGrid(_rows, _cols);

	for(Uint64 i=0; i<_rows; i++){
		for(Uint64 j=0; j<_cols; j++){
			if(i < rows && j < cols){
				newGrid[i][j] = grid[i][j];
			}
			else newGrid[i][j] = false;
		}
	}
	free(grid);
	return newGrid;
}

void moveGrid(double offsetX, double offsetY){
	gridOffX += offsetX;
	gridOffY += offsetY;
}

void flipCell(Grid grid, SDL_Point mouse){
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y][mouse.x] = !grid[mouse.y][mouse.x];
}

void clearGrid(Grid grid){
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			grid[i][j] = false;
		}
	}
}

void randomStartingState(Grid grid){
	for(Uint64 i=MARGIN/2; i<rows-MARGIN/2; i++){
		for(Uint64 j=MARGIN/2; j<cols-MARGIN/2; j++){
			grid[i][j] = rand()/(double)RAND_MAX > 0.5;
		}
	}
}

Uint8 getNeighbourSum(Grid grid, Uint64 i, Uint64 j){
	Uint8 sum = 0;
	for(Sint8 yoff=-1; yoff<=1; yoff++){
		for(Sint8 xoff=-1; xoff<=1; xoff++){
			if(xoff == 0 && yoff == 0) continue;
			Sint64 yIndex = i + yoff;
			Sint64 xIndex = j + xoff;
			if(yIndex>=0 && yIndex<rows && xIndex>=0 && xIndex<cols)
				sum += grid[yIndex][xIndex];
		}
	}
	return sum;
}

Grid nextState(Grid grid){
	Grid next = initGrid(rows, cols);

	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			next[i][j] = grid[i][j];
			Uint8 sum = getNeighbourSum(grid, i, j);
			if(grid[i][j]){
				next[i][j] = false;
				for(int k = 0; k < rule->slen; k++){
					if(sum == rule->s[k]) next[i][j] = true;
				}
			}
			else{
				for(int k = 0; k < rule->blen; k++){
					if(sum == rule->b[k]) next[i][j] = true;
				}
			}
		}
	}

	free(grid);
	return next;
}

void initRule(void){
	rule = malloc(sizeof *rule);
	rule->blen = 1;
	rule->b = malloc(rule->blen * sizeof *rule->b);
	rule->slen = 2;
	rule->s = malloc(rule->slen * sizeof *rule->s);

	rule->b[0] = 2;

	rule->s[0] = 2;
	rule->s[1] = 3;
}

void getRule(void){
	SDL_Rect* text = calloc(RULE_TEXT, sizeof *text);
	for(Uint8 i=0; i<RULE_TEXT; i++){
		text[i].w = 400;
		text[i].h = 80;
		text[i].x = SCREEN_WIDTH/2 - text[i].w/2;
		text[i].y = SCREEN_HEIGHT/6 * pow(3.5, i) - text[i].h/2;
	}

	SDL_Rect* buttons = calloc(RULE_BUTTONS, sizeof *buttons);
	for(Uint8 i=0; i<RULE_BUTTONS; i++){
		buttons[i].h = 100;
		buttons[i].w = 200;
		buttons[i].x = SCREEN_WIDTH/(RULE_BUTTONS+1) * (i+1) - buttons[i].w/2;
		buttons[i].y = SCREEN_HEIGHT/8 * 3 - buttons[i].h/2;
	}


	gettingRule = true;
	while(gettingRule){
		prepareScene(Black);

		for(Uint8 i=0; i<RULE_BUTTONS; i++){
			drawRect(buttons[i], White);
		}

		drawText("Select Rule", ruleFont, White, text[0]);
		drawText("Custom", ruleFont, White, text[1]);
		
		ruleInput();

		presentScene();
		
		SDL_Delay(50);
	}

	free(text);
	free(buttons);
}

void displayGrid(Grid grid){
	gridOffX = gridOffX < MARGIN/2*cellSize ? MARGIN/2*cellSize : gridOffX;
	gridOffY = gridOffY < MARGIN/2*cellSize ? MARGIN/2*cellSize : gridOffY;
	gridOffX = gridOffX > (cols-MARGIN/2)*cellSize - SCREEN_WIDTH ? (cols-MARGIN/2)*cellSize - SCREEN_WIDTH : gridOffX;
	gridOffY = gridOffY > (rows-MARGIN/2)*cellSize - SCREEN_HEIGHT ? (rows-MARGIN/2)*cellSize - SCREEN_HEIGHT : gridOffY;
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			if(grid[i][j]){
				SDL_Rect rect;
				rect.y = (Sint32) (i * cellSize + 1 - gridOffY);
				rect.x = (Sint32) (j * cellSize + 1 - gridOffX);
				rect.w = (Sint32) cellSize - 1;
				rect.h = (Sint32) rect.w;
				drawRect(rect, White);
			}
		}
	}
}

void drawGrid(Grid* grid){
	drawing = true;
	gridOffX = 20*cellSize;
	gridOffY = 20*cellSize;
	cellSize = DEFAULT_CELLSIZE;
	while(drawing){
		prepareScene(Black);
		
		gridInput(grid);

		displayGrid(*grid);

		presentScene();
		
		SDL_Delay(50);
	}
}

SDL_Point screenToGrid(Uint64 x, Uint64 y){
	SDL_Point index;
	index.x = (int)((double)(x + gridOffX)/cellSize);
	index.y = (int)((double)(y + gridOffY)/cellSize);
	return index;
}

void addGosperGun(Grid grid, SDL_Point mouse){
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y+0][mouse.x+25] = 1;

	grid[mouse.y+1][mouse.x+23] = 1;
	grid[mouse.y+1][mouse.x+25] = 1;

	grid[mouse.y+2][mouse.x+13] = 1;
	grid[mouse.y+2][mouse.x+14] = 1;
	grid[mouse.y+2][mouse.x+21] = 1;
	grid[mouse.y+2][mouse.x+22] = 1;
	grid[mouse.y+2][mouse.x+35] = 1;
	grid[mouse.y+2][mouse.x+36] = 1;

	grid[mouse.y+3][mouse.x+12] = 1;
	grid[mouse.y+3][mouse.x+16] = 1;
	grid[mouse.y+3][mouse.x+21] = 1;
	grid[mouse.y+3][mouse.x+22] = 1;
	grid[mouse.y+3][mouse.x+35] = 1;
	grid[mouse.y+3][mouse.x+36] = 1;

	grid[mouse.y+4][mouse.x+1] = 1;
	grid[mouse.y+4][mouse.x+2] = 1;
	grid[mouse.y+4][mouse.x+11] = 1;
	grid[mouse.y+4][mouse.x+17] = 1;
	grid[mouse.y+4][mouse.x+21] = 1;
	grid[mouse.y+4][mouse.x+22] = 1;

	grid[mouse.y+5][mouse.x+1] = 1;
	grid[mouse.y+5][mouse.x+2] = 1;
	grid[mouse.y+5][mouse.x+11] = 1;
	grid[mouse.y+5][mouse.x+15] = 1;
	grid[mouse.y+5][mouse.x+17] = 1;
	grid[mouse.y+5][mouse.x+18] = 1;
	grid[mouse.y+5][mouse.x+23] = 1;
	grid[mouse.y+5][mouse.x+25] = 1;

	grid[mouse.y+6][mouse.x+11] = 1;
	grid[mouse.y+6][mouse.x+17] = 1;
	grid[mouse.y+6][mouse.x+25] = 1;

	grid[mouse.y+7][mouse.x+12] = 1;
	grid[mouse.y+7][mouse.x+16] = 1;

	grid[mouse.y+8][mouse.x+13] = 1;
	grid[mouse.y+8][mouse.x+14] = 1;
}