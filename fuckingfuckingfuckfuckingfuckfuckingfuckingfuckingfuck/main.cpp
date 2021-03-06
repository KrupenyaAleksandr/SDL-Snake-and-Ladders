#include "head.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect rectsMenu[28]; // 0 - play, 1 - records, 2 - settings, 3 - exit, 4 - bluechip, 5 - redchip, 6 - move_button, 7 - dice
	rectsMenu[0] = { 368, 108, 500, 124 }; // play
	rectsMenu[1] = { 368, 328, 500, 124 }; // records
	rectsMenu[2] = { 368, 548, 500, 124 }; // settings
	rectsMenu[3] = { 368, 768, 500, 124 }; // exit
	rectsMenu[4] = { 17, 892, 45, 94 }; // bluechip
	rectsMenu[5] = { 64, 892, 45, 94 }; // redchip
	rectsMenu[6] = { 1041, 345, 140, 140 }; // move_button
	rectsMenu[7] = { 1061, 515, 100, 100 }; //dice
	rectsMenu[8] = { 0, 0, 100, 100 }; //dice - 1 (texture);
	rectsMenu[9] = { 100, 0, 100, 100 }; //dice - 2 (texture);
	rectsMenu[10] = { 200, 0, 100, 100 }; //dice - 3 (texture);
	rectsMenu[11] = { 300, 0, 100, 100 }; //dice - 4 (texture);
	rectsMenu[12] = { 400, 0, 100, 100 }; //dice - 5 (texture);
	rectsMenu[13] = { 500, 0, 100, 100 }; //dice - 6 (texture);
	rectsMenu[14] = {11, 11, 1010, 980}; // gamezone(doska)
	rectsMenu[15] = { 11, 11, 1010, 980 }; // texture
	rectsMenu[16] = {438, 466, 160, 200}; //record(1)
	rectsMenu[17] = {638, 466, 160, 200}; //record(2)
	rectsMenu[18] = {0, 0, 60, 100}; //0
	rectsMenu[19] = {60, 0, 60, 100}; //1
	rectsMenu[20] = {120, 0, 60, 100 }; //2
	rectsMenu[21] = {180, 0, 60, 100 }; //3
	rectsMenu[22] = {240, 0, 60, 100 }; //4
	rectsMenu[23] = {300, 0, 60, 100 }; //5
	rectsMenu[24] = {360, 0, 60, 100 }; //6
	rectsMenu[25] = {420, 0, 60, 100 }; //7
	rectsMenu[26] = {480, 0, 60, 100 }; //8
	rectsMenu[27] = {540, 0, 60, 100 }; //9

	initMenu(window, renderer, surface, texture, rectsMenu);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_Quit();
	return 0;
}