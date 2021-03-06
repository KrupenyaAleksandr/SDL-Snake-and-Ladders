#pragma once
#ifndef head
#define head

#include <iostream>
#include <time.h>
#include <sdl.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]);
void game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map, int& blueX0, int& blueY0, int& redX0, int& redY0, int& beforeW, int& beforeH, float& newW, float& newH, int& firstScore, int& secondScore, int& firstSteps, int& secondSteps, int& movingPlayer);
void initGame(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map, int& blueX0, int& blueY0, int& redX0, int& redY0, int& beforeW, int& beforeH, float& newW, float& newH, int firstScore, int secondScore, int firstSteps, int secondSteps, int movingPlayer);
void initMenu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]);
void drawMovingPlayer(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int player, int map);
void chipMoving(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int movingPlayer, int& playerScore, int map, int beforeW, int beforeH, float newW, float newH);
void resizeRects(SDL_Window* window, SDL_Rect rect[], int beforeW, int beforeH, float newW, float newH, int& blueX0, int& blueY0, int& redX0, int& redY0);
void saveFile(int blueX, int blueY, int redX, int redY, int firstScore, int secondScore, int firstSteps, int secondSteps, int movingPlayer, int map, int beforeW, int beforeH, float newW, float newH);
void loadFile(int& blueX, int& blueY, int& redX, int& redY, int& firstScore, int& secondScore, int& firstSteps, int& secondSteps, int& movingPlayer, int& map);
void chooseMap(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& map, int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0);
void showRecord(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0);
void chooseMode(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& map, int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0);

using namespace std;

#endif