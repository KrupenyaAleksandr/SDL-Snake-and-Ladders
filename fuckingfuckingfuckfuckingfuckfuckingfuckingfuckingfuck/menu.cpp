#include "head.h"

void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Event event;
	Mix_Chunk* BUTTON = Mix_LoadWAV("music/button.mp3");
	int blueX0 = 17, blueY0 = 892, redX0 = 64, redY0 = 892, beforeW = 1200, beforeH = 1000, W, H, player, first_score, second_score, map, first_steps = 0, second_steps = 0;
	float newW = 1200, newH = 1000;
	bool quit = false, initilization = true;
	while (!quit)
	{
		if (initilization) {
			cout << "menu" << endl;
			Mix_Chunk* BUTTON = Mix_LoadWAV("music/button.mp3");
			first_score = 1, second_score = 1, player = 1;
			rect[4].x = blueX0, rect[4].y = blueY0, rect[5].x = redX0, rect[5].y = redY0;
			surface = SDL_LoadBMP("texture/menu.bmp");
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
					surface = SDL_LoadBMP("texture/menu.bmp");
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
					chooseMode(event, window, renderer, surface, texture, rect, map, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
					if (map == -1) {
						chooseMap(event, window, renderer, surface, texture, rect, map, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
						if (map != 5) {
							initGame(window, renderer, surface, texture, rect, map, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, first_score, second_score, first_steps, second_steps, player);
						}
					}
					if (map == 4) {
						initGame(window, renderer, surface, texture, rect, map, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, first_score, second_score, first_steps, second_steps, player);
					}
					Mix_FreeChunk(BUTTON);
				}
				if (event.button.x >= rect[1].x && event.button.x <= rect[1].w + rect[3].x && event.button.y >= rect[1].y && event.button.y <= rect[1].h + rect[1].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					initilization = true;
					FILE* save = fopen("save.txt", "r");
					fseek(save, 0, SEEK_END);
					long pos = ftell(save);
					if (pos != 0) {
						fseek(save, 0, SEEK_SET);
						fclose(save);
						loadFile(rect[4].x, rect[4].y, rect[5].x, rect[5].y, first_score, second_score, first_steps, second_steps, player, map);
						//rect[4] = { int(rect[4].x * (newW / beforeW) + 0.5), int(rect[4].y * (newH / beforeH) + 0.5), rect[4].w, rect[4].h };
						//rect[5] = { int(rect[5].x * (newW / beforeW) + 0.5), int(rect[5].y * (newH / beforeH) + 0.5), rect[5].w, rect[5].h };
						initGame(window, renderer, surface, texture, rect, map, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, first_score, second_score, first_steps, second_steps, player);
						Mix_FreeChunk(BUTTON);
					}
					cout << "continue" << endl;
				}
				if (event.button.x >= rect[2].x && event.button.x <= rect[2].w + rect[2].x && event.button.y >= rect[2].y && event.button.y <= rect[2].h + rect[2].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					showRecord(event, window, renderer, surface, texture, rect, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
					initilization = true;
					cout << "records" << endl;
				}
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					SDL_Delay(300);
					cout << "quit" << endl;
					quit = true;
				} 
			} break;
			default: break;
			}
		}
	}
	Mix_FreeChunk(BUTTON);
}

void initMenu(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(u8"«меи и лестницы :)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_RESIZABLE );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Music* MENU = Mix_LoadMUS("music/C418 - Subwoofer Lullaby.mp3");
	Mix_VolumeMusic(1);
	Mix_PlayMusic(MENU, -1);

	menu(window, renderer, surface, texture,  rect);
}

void chooseMap(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& map, int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0) {
	int W, H;
	Mix_Chunk* BUTTON = Mix_LoadWAV("music/button.mp3");
	bool quit = false;
	surface = SDL_LoadBMP("texture/choose.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONUP: {
				if (event.button.x >= rect[0].x && event.button.x <= rect[0].w + rect[0].x && event.button.y >= rect[0].y && event.button.y <= rect[0].h + rect[0].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = 1;
					SDL_Delay(300);
					quit = true;
				}
				if (event.button.x >= rect[1].x && event.button.x <= rect[1].w + rect[3].x && event.button.y >= rect[1].y && event.button.y <= rect[1].h + rect[1].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = 2;
					SDL_Delay(300);
					quit = true;
				}
				if (event.button.x >= rect[2].x && event.button.x <= rect[2].w + rect[2].x && event.button.y >= rect[2].y && event.button.y <= rect[2].h + rect[2].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = 3;
					SDL_Delay(300);
					quit = true;
				}
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = 5;
					SDL_Delay(300);
					quit = true;
				}
			} break;
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					surface = SDL_LoadBMP("texture/choose.bmp");
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
			} break;
			}
		}
	}
	Mix_FreeChunk(BUTTON);
}

void resizeRects(SDL_Window* window, SDL_Rect rect[], int beforeW, int beforeH, float newW, float newH, int& blueX0, int& blueY0, int& redX0, int& redY0) {

	float tmpWIDTH, tmpHEIGHT;
	int tblueX, tblueY, tredX, tredY, tmove, tmap, tfirst, tsecond, tfirstmove, tsecondmove, tbW = beforeW, tbH = beforeH;
	float tnW = newW, tnH = newH;

	rect[0] = { int(rect[0].x * (newW / beforeW) + 0.5), int(rect[0].y * (newH / beforeH) + 0.5), int(rect[0].w * (newW / beforeW) + 0.5), int(rect[0].h * (newH / beforeH) + 0.5) }; // play
	rect[1] = { int(rect[1].x * (newW / beforeW) + 0.5), int(rect[1].y * (newH / beforeH) + 0.5), int(rect[1].w * (newW / beforeW) + 0.5), int(rect[1].h * (newH / beforeH) + 0.5) }; // records
	rect[2] = { int(rect[2].x * (newW / beforeW) + 0.5), int(rect[2].y * (newH / beforeH) + 0.5), int(rect[2].w * (newW / beforeW) + 0.5), int(rect[2].h * (newH / beforeH) + 0.5) }; // settings
	rect[3] = { int(rect[3].x * (newW / beforeW) + 0.5), int(rect[3].y * (newH / beforeH) + 0.5), int(rect[3].w * (newW / beforeW) + 0.5), int(rect[3].h * (newH / beforeH) + 0.5) }; // exit
	rect[4] = { int(rect[4].x * (newW / beforeW) + 0.5), int(rect[4].y * (newH / beforeH) + 0.5), int(rect[4].w * (newW / beforeW) + 0.5), int(rect[4].h * (newH / beforeH) + 0.5) }; // bluechip
	rect[5] = { int(rect[5].x * (newW / beforeW) + 0.5), int(rect[5].y * (newH / beforeH) + 0.5), int(rect[5].w * (newW / beforeW) + 0.5), int(rect[5].h * (newH / beforeH) + 0.5) }; // redchip
	rect[6] = { int(rect[6].x * (newW / beforeW) + 0.5), int(rect[6].y * (newH / beforeH) + 0.5), int(rect[6].w * (newW / beforeW) + 0.5), int(rect[6].h * (newH / beforeH) + 0.5) }; // move_button
	rect[7] = { int(rect[7].x * (newW / beforeW) + 0.5), int(rect[7].y * (newH / beforeH) + 0.5), int(rect[7].w * (newW / beforeW) + 0.5), int(rect[7].h * (newH / beforeH) + 0.5) }; // dice
	rect[14] = { int(rect[14].x * (newW / beforeW) + 0.5), int(rect[14].y * (newH / beforeH) + 0.5), int(rect[14].w * (newW / beforeW) + 0.5), int(rect[14].h * (newH / beforeH) + 0.5) }; // gamezone
	rect[16] = { int(rect[16].x * (newW / beforeW) + 0.5), int(rect[16].y * (newH / beforeH) + 0.5), int(rect[16].w * (newW / beforeW) + 0.5), int(rect[16].h * (newH / beforeH) + 0.5) }; // record(1)
	rect[17] = { int(rect[17].x * (newW / beforeW) + 0.5), int(rect[17].y * (newH / beforeH) + 0.5), int(rect[17].w * (newW / beforeW) + 0.5), int(rect[17].h * (newH / beforeH) + 0.5) }; // record(1)

	blueX0 = int(17 * (newW / 1200) + 0.5);
	blueY0 = int(892 * (newH / 1000) + 0.5);
	redX0 = int(64 * (newW / 1200) + 0.5);
	redY0 = int(892 * (newH / 1000) + 0.5);

	loadFile(tblueX, tblueY, tredX, tredY, tfirst, tsecond, tfirstmove, tsecondmove, tmove, tmap);
	tblueX = int(tblueX * (newW / beforeW) + 0.5);
	tblueY = int(tblueY * (newH / beforeH) + 0.5);
	tredX = int(tredX * (newW / beforeW) + 0.5);
	tredY = int(tredY * (newH / beforeH) + 0.5);
	saveFile(tblueX, tblueY, tredX, tredY, tfirst, tsecond, tfirstmove, tsecondmove, tmove, tmap, tbW, tbH, tnW, tnH);
}

void saveFile(int blueX, int blueY, int redX, int redY, int firstScore, int secondScore, int firstSteps, int secondSteps, int movingPlayer, int map, int beforeW, int beforeH, float newW, float newH) {
	//int W = newW, H = newH;
	FILE* f = fopen("save.txt", "w");
	//fprintf(f, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", int(blueX * (beforeW / newW) + 0.5), int(blueY * (beforeH / newH) + 0.5), int(redX * (beforeW / newW) + 0.5), int(redY * (beforeH / newH) + 0.5), firstScore, secondScore, firstSteps, secondSteps, movingPlayer, map, beforeW, beforeH, W, H);
	fprintf(f, "%d %d %d %d %d %d %d %d %d %d", int(blueX * (beforeW / newW) + 0.5), int(blueY * (beforeH / newH) + 0.5), int(redX * (beforeW / newW) + 0.5), int(redY * (beforeH / newH) + 0.5), firstScore, secondScore, firstSteps, secondSteps, movingPlayer, map);
	fclose(f);
}

void loadFile(int& blueX, int& blueY, int& redX, int& redY, int& firstScore, int& secondScore, int& firstSteps, int& secondSteps, int& movingPlayer, int& map) {
	int W, H;
	FILE* f = fopen("save.txt", "r");
	//fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &blueX, &blueY, &redX, &redY, &firstScore, &secondScore, &firstSteps, &secondSteps, &movingPlayer, &map, &W, &H, &beforeW, &beforeH);
	//newW = W, newH = H;
	fscanf(f, "%d %d %d %d %d %d %d %d %d %d", &blueX, &blueY, &redX, &redY, &firstScore, &secondScore, &firstSteps, &secondSteps, &movingPlayer, &map);
	fclose(f);
}

void showRecord(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0) {
	Mix_Chunk* BUTTON = Mix_LoadWAV("music/button.mp3");
	int record = 0, W, H, number = 0, tmp;
	bool quit = false;
	FILE* rec = fopen("record.txt", "r");
	fseek(rec, 0, SEEK_END);
	long pos = ftell(rec);
	if (pos != 0) {
		fseek(rec, 0, SEEK_SET);
		fscanf(rec, "%d", &record);
	}
	fclose(rec);
	surface = SDL_LoadBMP("texture/record.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
	while (!quit) {
		if (record != 0) {
			tmp = record;
			surface = SDL_LoadBMP("texture/numbersrecord.bmp");
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			for (int i = 0; i < 2; i++) {
				number = record % 10;
				switch (number) {
				case 0: { SDL_RenderCopy(renderer, texture, &rect[18], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 1: { SDL_RenderCopy(renderer, texture, &rect[19], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 2: { SDL_RenderCopy(renderer, texture, &rect[20], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 3: { SDL_RenderCopy(renderer, texture, &rect[21], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 4: { SDL_RenderCopy(renderer, texture, &rect[22], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 5: { SDL_RenderCopy(renderer, texture, &rect[23], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 6: { SDL_RenderCopy(renderer, texture, &rect[24], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 7: { SDL_RenderCopy(renderer, texture, &rect[25], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 8: { SDL_RenderCopy(renderer, texture, &rect[26], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				case 9: { SDL_RenderCopy(renderer, texture, &rect[27], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
				}
				record /= 10;
			}
			SDL_DestroyTexture(texture);
			record = tmp;
		}
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONUP: {
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					quit = true;
					SDL_Delay(300);
				}

			} break;
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					surface = SDL_LoadBMP("texture/record.bmp");
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_RenderPresent(renderer);
					SDL_DestroyTexture(texture);
					beforeW = newW, beforeH = newH;
					SDL_GetWindowSize(window, &W, &H);
					newW = W, newH = H;
					resizeRects(window, rect, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
					if (record != 0) {
						tmp = record;
						surface = SDL_LoadBMP("texture/numbersrecord.bmp");
						texture = SDL_CreateTextureFromSurface(renderer, surface);
						SDL_FreeSurface(surface);
						for (int i = 0; i < 2; i++) {
							number = record % 10;
							switch (number) {
							case 0: { SDL_RenderCopy(renderer, texture, &rect[18], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 1: { SDL_RenderCopy(renderer, texture, &rect[19], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 2: { SDL_RenderCopy(renderer, texture, &rect[20], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 3: { SDL_RenderCopy(renderer, texture, &rect[21], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 4: { SDL_RenderCopy(renderer, texture, &rect[22], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 5: { SDL_RenderCopy(renderer, texture, &rect[23], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 6: { SDL_RenderCopy(renderer, texture, &rect[24], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 7: { SDL_RenderCopy(renderer, texture, &rect[25], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 8: { SDL_RenderCopy(renderer, texture, &rect[26], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							case 9: { SDL_RenderCopy(renderer, texture, &rect[27], &rect[17 - i]); SDL_RenderPresent(renderer); } break;
							}
							record /= 10;
						}
						SDL_DestroyTexture(texture);
						record = tmp;
					}
				} break;
			}
			}
		}
	}
	Mix_FreeChunk(BUTTON);
}

void chooseMode(SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int& map, int& beforeW, int& beforeH, float& newW, float& newH, int& blueX0, int& blueY0, int& redX0, int& redY0) {
	bool quit = false;
	int W, H;
	Mix_Chunk* BUTTON = Mix_LoadWAV("music/button.mp3");
	surface = SDL_LoadBMP("texture/mode.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					surface = SDL_LoadBMP("texture/mode.bmp");
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
			} break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.x >= rect[1].x && event.button.x <= rect[1].w + rect[3].x && event.button.y >= rect[1].y && event.button.y <= rect[1].h + rect[1].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = -1;
					SDL_Delay(300);
					quit = true;
				}
				if (event.button.x >= rect[2].x && event.button.x <= rect[2].w + rect[2].x && event.button.y >= rect[2].y && event.button.y <= rect[2].h + rect[2].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					map = 4;
					SDL_Delay(300);
					quit = true;
				}
				if (event.button.x >= rect[3].x && event.button.x <= rect[3].w + rect[3].x && event.button.y >= rect[3].y && event.button.y <= rect[3].h + rect[3].y) {
					Mix_PlayChannel(-1, BUTTON, 0);
					SDL_Delay(300);
					quit = true;
				}
			}
		}
	}
	Mix_FreeChunk(BUTTON);
}