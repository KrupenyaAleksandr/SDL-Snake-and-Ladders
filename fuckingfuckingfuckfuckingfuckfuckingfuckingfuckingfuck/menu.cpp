#include "head.h"

void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Event event;
	Mix_Chunk* BUTTON = Mix_LoadWAV("button.mp3");
	int blueX0, blueY0, redX0, redY0, beforeW = 1200, beforeH = 1000, W, H, player, first_score, second_score, map = 1;
	float newW = 1200, newH = 1000;
	bool quit = false, initilization = true;
	while (!quit)
	{
		if (initilization) {
			cout << "menu" << endl;
			Mix_Chunk* BUTTON = Mix_LoadWAV("button.mp3");
			first_score = 1, second_score = 1, player = 1, blueX0 = rect[4].x = 17, blueY0 = rect[4].y = 892, redX0 = rect[5].x = 64, redY0 = rect[5].y = 892;
			surface = SDL_LoadBMP("menu.bmp");
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_DestroyTexture(texture);
			initilization = false;
		}
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: { quit = true; } break;
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					surface = SDL_LoadBMP("menu.bmp");
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_RenderPresent(renderer);
					SDL_DestroyTexture(texture);
					beforeW = newW, beforeH = newH;
					SDL_GetWindowSize(window, &W, &H); 
					newW = W, newH = H;
					resizeRects(window, rect, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
				}
				else { break; }
			} break;
			case SDL_MOUSEBUTTONUP: {
				if (event.button.x >= rect[0].x && event.button.x <= rect[0].w + rect[0].x && event.button.y >= rect[0].y && event.button.y <= rect[0].h + rect[0].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					cout << "play" << endl;
					initilization = true;
					initGame(window, renderer, surface, texture, rect, map, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, first_score, second_score, player);
					Mix_FreeChunk(BUTTON);
				}
				if (event.button.x >= rect[1].x && event.button.x <= rect[1].w + rect[3].x && event.button.y >= rect[1].y && event.button.y <= rect[1].h + rect[1].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					initilization = true;
					loadFile(rect[4].x, rect[4].y, rect[5].x, rect[5].y, first_score, second_score, player, map);
					initGame(window, renderer, surface, texture, rect, map, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, first_score, second_score, player);
					Mix_FreeChunk(BUTTON);
					cout << "continue" << endl;
				}
				if (event.button.x >= rect[2].x && event.button.x <= rect[2].w + rect[2].x && event.button.y >= rect[2].y && event.button.y <= rect[2].h + rect[2].y) {
					Mix_PlayChannel(-1, BUTTON, 0);

					cout << "settings" << endl;
				}
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y){
					Mix_PlayChannel(-1, BUTTON, 0);
					SDL_Delay(300);
					cout << "quit" << endl; 
					quit = true;}
				else { break;  }
			} break;
			default: break;
			}
		}
	}
}

void initMenu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(u8"трахал", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Music* MENU = Mix_LoadMUS("C418 - Subwoofer Lullaby.mp3");
	Mix_VolumeMusic(1);
	Mix_PlayMusic(MENU, -1);

	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("HATTEN.ttf", 70);

	menu(window, renderer, surface, texture,  rect);
}

void resizeRects(SDL_Window* window, SDL_Rect rect[], int beforeW, int beforeH, float newW, float newH, int& blueX0, int& blueY0, int& redX0, int& redY0) {

	float tmpWIDTH, tmpHEIGHT;
	int tblueX, tblueY, tredX, tredY, tmove, tmap, tfirst, tsecond;

	rect[0] = { int(rect[0].x * (newW / beforeW) + 0.5), int(rect[0].y * (newH / beforeH) + 0.5), int(rect[0].w * (newW / beforeW) + 0.5), int(rect[0].h * (newH / beforeH) + 0.5) }; // play
	rect[1] = { int(rect[1].x * (newW / beforeW) + 0.5), int(rect[1].y * (newH / beforeH) + 0.5), int(rect[1].w * (newW / beforeW) + 0.5), int(rect[1].h * (newH / beforeH) + 0.5) }; // records
	rect[2] = { int(rect[2].x * (newW / beforeW) + 0.5), int(rect[2].y * (newH / beforeH) + 0.5), int(rect[2].w * (newW / beforeW) + 0.5), int(rect[2].h * (newH / beforeH) + 0.5) }; // settings
	rect[3] = { int(rect[3].x * (newW / beforeW) + 0.5), int(rect[3].y * (newH / beforeH) + 0.5), int(rect[3].w * (newW / beforeW) + 0.5), int(rect[3].h * (newH / beforeH) + 0.5) }; // exit
	rect[4] = { int(rect[4].x * (newW / beforeW) + 0.5), int(rect[4].y * (newH / beforeH) + 0.5), int(rect[4].w * (newW / beforeW) + 0.5), int(rect[4].h * (newH / beforeH) + 0.5) }; // bluechip
	rect[5] = { int(rect[5].x * (newW / beforeW) + 0.5), int(rect[5].y * (newH / beforeH) + 0.5), int(rect[5].w * (newW / beforeW) + 0.5), int(rect[5].h * (newH / beforeH) + 0.5) }; // redchip
	rect[6] = { int(rect[6].x * (newW / beforeW) + 0.5), int(rect[6].y * (newH / beforeH) + 0.5), int(rect[6].w * (newW / beforeW) + 0.5), int(rect[6].h * (newH / beforeH) + 0.5) }; // move_button
	rect[7] = { int(rect[7].x * (newW / beforeW) + 0.5), int(rect[7].y * (newH / beforeH) + 0.5), int(rect[7].w * (newW / beforeW) + 0.5), int(rect[7].h * (newH / beforeH) + 0.5) }; // dice
	rect[14] = { int(rect[14].x * (newW / beforeW) + 0.5), int(rect[14].y * (newH / beforeH) + 0.5), int(rect[14].w * (newW / beforeW) + 0.5), int(rect[14].h * (newH / beforeH) + 0.5) }; // gamezone

	blueX0 = int(17 * (newW / 1200) + 0.5);
	blueY0 = int(892 * (newH / 1000) + 0.5);
	redX0 = int(64 * (newW / 1200) + 0.5);
	redY0 = int(892 * (newH / 1000) + 0.5);

	loadFile(tblueX, tblueY, tredX, tredY, tfirst, tsecond, tmove, tmap);
	tblueX = int(tblueX * (newW / beforeW) + 0.5);
	tblueY = int(tblueY * (newH / beforeH) + 0.5);
	tredX = int(tredX * (newW / beforeW) + 0.5);
	tredY = int(tredY * (newH / beforeH) + 0.5);
	saveFile(tblueX, tblueY, tredX, tredY, tfirst, tsecond, tmove, tmap);
}

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 255, 255, 255 };
	textSurface = TTF_RenderUTF8_Blended(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

//void resizeRects(SDL_Window* window, SDL_Rect rect[], int blueX, int blueY, int redX, int redY) {
//	int WIDTH, HEIGHT;
//	float tmpWIDTH, tmpHEIGHT;
//	SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
//	tmpWIDTH = WIDTH; tmpHEIGHT = HEIGHT;
//
//	rect[0] = { int(368 * (tmpWIDTH / 1200)), int(108 * (tmpHEIGHT / 1000)), int(500 * (tmpWIDTH / 1200)), int(124 * (tmpHEIGHT / 1000)) }; // play
//	rect[1] = { int(368 * (tmpWIDTH / 1200)), int(328 * (tmpHEIGHT / 1000)), int(500 * (tmpWIDTH / 1200)), int(124 * (tmpHEIGHT / 1000)) }; // records
//	rect[2] = { int(368 * (tmpWIDTH / 1200)), int(548 * (tmpHEIGHT / 1000)), int(500 * (tmpWIDTH / 1200)), int(124 * (tmpHEIGHT / 1000)) }; // settings
//	rect[3] = { int(368 * (tmpWIDTH / 1200)), int(768 * (tmpHEIGHT / 1000)), int(500 * (tmpWIDTH / 1200)), int(124 * (tmpHEIGHT / 1000)) }; // exit
//	rect[4] = { int(blueX * (tmpWIDTH / 1200)), int(blueY * (tmpHEIGHT / 1000)), int(45 * (tmpWIDTH / 1200)), int(94 * (tmpHEIGHT / 1000)) }; // bluechip
//	rect[5] = { int(redX * (tmpWIDTH / 1200)), int(redY * (tmpHEIGHT / 1000)), int(45 * (tmpWIDTH / 1200)), int(94 * (tmpHEIGHT / 1000)) }; // redchip
//	rect[6] = { int(1041 * (tmpWIDTH / 1200)), int(345 * (tmpHEIGHT / 1000)), int(140 * (tmpWIDTH / 1200)), int(140 * (tmpHEIGHT / 1000)) }; // move_button
//	rect[7] = { int(1061 * (tmpWIDTH / 1200)), int(515 * (tmpHEIGHT / 1000)), int(100 * (tmpWIDTH / 1200)), int(100 * (tmpHEIGHT / 1000)) }; // dice
//	rect[14] = { int(11 * (tmpWIDTH / 1200)), int(11 * (tmpHEIGHT / 1000)), int(1010 * (tmpWIDTH / 1200)), int(980 * (tmpHEIGHT / 1000)) }; // gamezone
//}
