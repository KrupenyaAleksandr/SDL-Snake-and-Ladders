#include "head.h"

void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Event event;
	int blueX = 17, blueY = 892, redX = 64, redY = 892, beforeW = 1200, beforeH = 1000, W = 0, H = 0;
	float newW, newH;
	bool quit = false, initilization = true;
	while (!quit)
	{
		if (initilization) {
			cout << "menu" << endl;
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
					SDL_GetWindowSize(window, &W, &H);
					newW = W, newH = H;
					resizeRects(window, rect, beforeW, beforeH, newW, newH);
					beforeW = newW, beforeH = newH;
				}
				else { break; }
			} break;
			case SDL_MOUSEBUTTONUP: {
				if (event.button.x >= rect[0].x && event.button.x <= rect[0].w + rect[0].x && event.button.y >= rect[0].y && event.button.y <= rect[0].h + rect[0].y) {
					cout << "play" << endl;
					initilization = true;
					initGame(window, renderer, surface, texture, rect, 1);
				}
				if (event.button.x >= rect[1].x && event.button.x <= rect[1].w + rect[3].x && event.button.y >= rect[1].y && event.button.y <= rect[1].h + rect[1].y) {
					cout << "records" << endl;
				}
				if (event.button.x >= rect[2].x && event.button.x <= rect[2].w + rect[2].x && event.button.y >= rect[2].y && event.button.y <= rect[2].h + rect[2].y) {
					cout << "settings" << endl;
				}
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y){ cout << "quit" << endl; quit = true;}
				else { break;  }
			} break;
			default: break;
			}
		}
	}
}

void initMenu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(u8"трахал", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

void resizeRects(SDL_Window* window, SDL_Rect rect[], int beforeW, int beforeH, float newW, float newH) {

	float tmpWIDTH, tmpHEIGHT;


	rect[0] = { int(rect[0].x * (newW / beforeW)) + 1, int(rect[0].y * (newH / beforeH)), int(rect[0].w * (newW / beforeW)), int(rect[0].h * (newH / beforeH)) }; // play
	rect[1] = { int(rect[1].x * (newW / beforeW)) + 1, int(rect[1].y * (newH / beforeH)), int(rect[1].w * (newW / beforeW)), int(rect[1].h * (newH / beforeH)) }; // records
	rect[2] = { int(rect[2].x * (newW / beforeW)) + 1, int(rect[2].y * (newH / beforeH)), int(rect[2].w * (newW / beforeW)), int(rect[2].h * (newH / beforeH)) }; // settings
	rect[3] = { int(rect[3].x * (newW / beforeW)) + 1, int(rect[3].y * (newH / beforeH)), int(rect[3].w * (newW / beforeW)), int(rect[3].h * (newH / beforeH)) }; // exit
	rect[4] = { int(rect[4].x * (newW / beforeW)) + 1, int(rect[4].y * (newH / beforeH)), int(rect[4].w * (newW / beforeW)), int(rect[4].h * (newH / beforeH)) }; // bluechip
	rect[5] = { int(rect[5].x * (newW / beforeW)) + 1, int(rect[5].y * (newH / beforeH)), int(rect[5].w * (newW / beforeW)), int(rect[5].h * (newH / beforeH)) }; // redchip
	rect[6] = { int(rect[6].x * (newW / beforeW)) + 1, int(rect[6].y * (newH / beforeH)), int(rect[6].w * (newW / beforeW)), int(rect[6].h * (newH / beforeH)) }; // move_button
	rect[7] = { int(rect[7].x * (newW / beforeW)) + 1, int(rect[7].y * (newH / beforeH)), int(rect[7].w * (newW / beforeW)), int(rect[7].h * (newH / beforeH)) }; // dice
	rect[14] = { int(rect[14].x * (newW / beforeW)) + 1, int(rect[14].y * (newH / beforeH)), int(rect[14].w * (newW / beforeW)), int(rect[14].h * (newH / beforeH)) }; // gamezone

	//rect[4] = { int(blueX * (newW / beforeW)) + 1, int(blueY * (newH / beforeH)), int(rect[4].w * (newW / beforeW)), int(rect[4].h * (newH / beforeH)) }; // bluechip
	//rect[5] = { int(redX * (newW / beforeW)) + 1, int(redY * (newH / beforeH)), int(rect[5].w * (newW / beforeW)), int(rect[5].h * (newH / beforeH)) }; // redchip
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
