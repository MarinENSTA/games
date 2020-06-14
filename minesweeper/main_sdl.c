#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include "minesweeperModule.h"

/* 
DISCLAIMER : I HAVEN'T REALLY THOUGHT ABOUT WINDOW AND GRIDSIZE MODIFICATION YET.
PLEASE AVOID CHANGING THESE (at least not too much...)
*/
#define WINDOWSIZE 800
#define GRIDSIZE 20

// Feel free to change this to increase/decrease difficulty. (Not more than gridsize^2, though.)
#define MINES 30

// Initialising all functions.
void SDL_ExitError(const char *message);
int GridCoord(int coord);
void initGrid(SDL_Renderer *renderer);
SDL_Color* initColors();
void TextInRect(int xg, int yg, int neighbours, SDL_Color color, SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *wrect,SDL_Rect *coloRect,SDL_Texture **texture);



int main (int argc, char** argv)
{

	/**********************INITIALISATION*********************************************************************/

	//Initializing the minesweeper grid
	if (MINES > GRIDSIZE*GRIDSIZE)
	{
		printf("\nTOO MANY MINES : MAX IS %d for current grid.\nPlease change MINES value and program will work just fine.\n \n", GRIDSIZE*GRIDSIZE);
		exit(EXIT_FAILURE);
	}

	struct cas** table=creer_grille(GRIDSIZE);
	placement(table,GRIDSIZE,MINES);
	SDL_bool program_launched = SDL_TRUE;
	int end = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect writeRect;
	SDL_Rect coloRect;
	SDL_Texture *texture1;
	int xc,yc;
	int xg,yg;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL Video initialisation error.\n");
	}

	if (TTF_Init() == -1)
		printf("TTF initialisation error.\n");


    TTF_Font* Sans = TTF_OpenFont("OpenSans-Bold.ttf", 24*GRIDSIZE/20); 
    if (Sans == NULL)
    	printf("Font initialisation error (maybe not found)\n Usually works fine when adding font to local folder.\n");


    SDL_Color* colors=initColors();


    if (SDL_CreateWindowAndRenderer(WINDOWSIZE,WINDOWSIZE, 0, &window, &renderer) != 0) 
    	printf("Window and renderer initialisation error.");

    SDL_SetWindowTitle(window, "Minesweeper");

        //SDL_RenderClear(renderer) (not useful here actually);
	if (SDL_SetRenderDrawColor(renderer,210,210,210,SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitError("Error loading new color to renderer");

	initGrid(renderer);
	SDL_RenderPresent(renderer);

	/********************************MAINLOOP**********************************************/



	while(program_launched)
	{
		SDL_Event event;

		while(SDL_WaitEvent(&event)) 
		{
			switch(event.type)
			{
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							program_launched = SDL_FALSE;
							break;

						case SDLK_BACKSPACE:
							program_launched = SDL_FALSE;
							break;

						// PRESSING ENTER ONCE GAME IS EITHER WON OR LOST WILL RESET GAME WITH NEW GRID
						// Checks if end == 0 in order not to reset when game isn't finished
						case SDLK_RETURN:
							if (end !=0)
							{
								table = creer_grille(GRIDSIZE);
								placement(table,GRIDSIZE,MINES);
								end = 0;
								SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
								SDL_RenderClear(renderer);
								SDL_SetRenderDrawColor(renderer,210,210,210,SDL_ALPHA_OPAQUE);
								initGrid(renderer);
								SDL_RenderPresent(renderer);
							}

						default:
							break;
					}

				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button)
						{
						case SDL_BUTTON_LEFT:
							xc = event.button.x;
							yc = event.button.y;
							xg = GridCoord(xc);
							yg = GridCoord(yc);
							end = sdltour(table,GRIDSIZE,MINES,end,xg,yg);

							//printf("end = %d\n",end);
							if (end == 1)
								printf("Victory !\n PRESS ENTER TO START A NEW GAME\n");
							else if (end == -1)
								printf("PRESS ENTER TO START A NEW GAME\n");

							//LEFT-CLICK will by default trigger redrawing the entire grid (as some mines may have been discovered)
							for (int i = 0 ; i < GRIDSIZE ; i++)
							{
								for (int j = 0 ; j < GRIDSIZE ; j++)
								{

									if (end != 0)
									{
										table[i][j].boole=1;
									}
									

									if (table[i][j].boole==1)
									{	
										TextInRect(i, j, table[i][j].val, colors[table[i][j].val], renderer, Sans, &writeRect,&coloRect,&texture1);
										SDL_RenderFillRect(renderer, &coloRect);
										if (table[i][j].val != 0)
											SDL_RenderCopy(renderer, texture1, NULL, &writeRect);
										
									}
								}
							}

							SDL_RenderPresent(renderer);
							//printf("Left click on %d/%d\n", xg, yg);
							break;

						// RIGHT CLICK WILL FLAG A MINE 
						case SDL_BUTTON_RIGHT:
							xc = event.button.x;
							yc = event.button.y;
							xg = GridCoord(xc);
							yg = GridCoord(yc);

							coloRect.x = 1 + (WINDOWSIZE / GRIDSIZE) * xg + (WINDOWSIZE / GRIDSIZE)/4; 
							coloRect.y = 1 + (WINDOWSIZE / GRIDSIZE) * yg + (WINDOWSIZE / GRIDSIZE)/4; 
							coloRect.w = (WINDOWSIZE / GRIDSIZE)/2;
							coloRect.h = (WINDOWSIZE / GRIDSIZE)/2;

							//We of course check if mine is already flagged, in which case we unflag it
							if(table[xg][yg].boole==0 && table[xg][yg].flagged==0)
							{
								SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
								SDL_RenderFillRect(renderer, &coloRect);
								SDL_RenderPresent(renderer);
								SDL_SetRenderDrawColor(renderer,210,210,210,SDL_ALPHA_OPAQUE);
								table[xg][yg].flagged = 1;
							}

							else if (table[xg][yg].boole == 0 && table[xg][yg].flagged != 0)
							{
								SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
								SDL_RenderFillRect(renderer, &coloRect);
								SDL_RenderPresent(renderer);
								SDL_SetRenderDrawColor(renderer,210,210,210,SDL_ALPHA_OPAQUE);
								table[xg][yg].flagged = 0;

							}

							//printf("Left click on %d/%d\n", xg, yg);
							break;
						}

			}

		}

	}


	/***************************************ENDING MAIN, FREEING EVERYTHING******************************************/
	free(colors);
	TTF_Quit();
	SDL_DestroyTexture(texture1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}


void SDL_ExitError(const char *message)
{
	SDL_Log("ERREUR : %s\n", SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}


int GridCoord(int coord)
{
	return (int)(coord / (WINDOWSIZE/GRIDSIZE));
}

void initGrid(SDL_Renderer *renderer)
{
	int j;
	for (int i = 0; i<GRIDSIZE; i++)
	{
		j = i*(WINDOWSIZE/GRIDSIZE);
		if(SDL_RenderDrawLine(renderer,0,j, WINDOWSIZE,j) != 0)
			printf("Line rendering error between points %d/%d and %d/%d\n", 0,j,WINDOWSIZE,j);

		if(SDL_RenderDrawLine(renderer,j,0, j,WINDOWSIZE) != 0)
			printf("Line rendering error between points %d/%d and %d/%d\n", j,0,j,WINDOWSIZE);
	}

	// Drawing the two edge lines (looks better)
	if(SDL_RenderDrawLine(renderer,0,WINDOWSIZE-1, WINDOWSIZE-1,WINDOWSIZE-1) != 0)
		SDL_ExitError("Error drawing edge line");
	if(SDL_RenderDrawLine(renderer,WINDOWSIZE-1,0, WINDOWSIZE-1,WINDOWSIZE-1) != 0)
		SDL_ExitError("Erreur drawing edge line");
}


void TextInRect(int xg, int yg, int neighbours, SDL_Color color, SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *wrect, SDL_Rect *coloRect,SDL_Texture **texture) 
{

	char strneighs[5];

	if (strneighs == NULL)
		printf("Error when initializing string in TextInRect");

	// 9 corresponds to a mine in our table. We don't want a 9 to be displayed. X looks better.
	if (neighbours == 9)
		strneighs[0] = 'X';

	//TTF_RenderText_Solid takes as string as an argument. We therefore convert the number of neighbour mines into a string.
	else
		sprintf(strneighs, "%d", neighbours);


	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, strneighs, color); 
	if (surfaceMessage == NULL)
		printf("Error when creating surfaceMessage in TextInRect using TTF_RenderText_Solid");

    *texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
    if (texture == NULL)
    	printf("Error using SDL_CreateTextureFromSurface in TextInRect");

	//SDL_FreeSurface(surfaceMessage); 
	wrect->x = 30 - GRIDSIZE + (WINDOWSIZE / GRIDSIZE) * xg;  //10
	wrect->y = 20 - GRIDSIZE + (WINDOWSIZE / GRIDSIZE) * yg;  //5
	wrect->w = 800*(2*20-GRIDSIZE)/WINDOWSIZE; 
	wrect->h = 800*(2*30-GRIDSIZE)/WINDOWSIZE; 
	coloRect->x = 1 + (WINDOWSIZE / GRIDSIZE) * xg; 
	coloRect->y = 1 + (WINDOWSIZE / GRIDSIZE) * yg; 
	coloRect->w = -1 + WINDOWSIZE / GRIDSIZE;
	coloRect->h = -1 + WINDOWSIZE / GRIDSIZE;
}


SDL_Color* initColors()
{
	SDL_Color* colors=malloc(8*sizeof(SDL_Color));

	if (colors == NULL)
		printf("Error when initializing colors list");

	SDL_Color lgray = {230,230,230};
	colors[0] = lgray;
    SDL_Color one = {0, 0, 255};
    colors[1] = one;
	SDL_Color two = {0, 255, 0};
	colors[2] = two;
	SDL_Color three = {255,0,0};
	colors[3] = three;
	SDL_Color four = {72,61,139};
	colors[4] = four;
	SDL_Color five = {0, 0, 0};
	colors[5] = five;
	SDL_Color six = {244,164,96};
	colors[6] = six;
	SDL_Color seven = {255, 0, 255};
	colors[7] = seven;
	SDL_Color eight = {0,255,255};
	colors[8] = eight;

	return colors;
}



// gcc main_sdl.c minesweeperModule.c -o test.exe $(sdl2-config --cflags --libs) -lSDL_image -lSDL2_ttf
