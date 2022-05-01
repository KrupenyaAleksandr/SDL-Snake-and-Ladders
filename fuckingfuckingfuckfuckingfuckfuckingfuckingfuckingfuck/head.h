#pragma once
#ifndef head
#define head

#include <iostream>
#include <time.h>
#include <sdl.h>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]);
void game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map);
void initGame(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map);
void initMenu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]);
void drawChips(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]);  // убрать лишние параметры
void drawMovingPlayer(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int player, int map);
/*void chipMoving(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int movingPlayer, int& playerScore, int map);*/
void chipMoving(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int movingPlayer, int& playerScore, int map, int& blueX, int& blueY, int& redX, int& redY, int beforeW, int beforeH);
void resizeRects(SDL_Window* window, SDL_Rect rect[], int blueX, int blueY, int redX, int redY, int beforeW, int beforeH, float newW, float newH);
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font);

using namespace std;

#endif