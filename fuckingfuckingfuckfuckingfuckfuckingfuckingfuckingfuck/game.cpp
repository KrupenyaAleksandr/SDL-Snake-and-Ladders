#include "head.h"

void game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map, int& blueX0, int& blueY0, int& redX0, int& redY0, int& beforeW, int& beforeH, float& newW, float& newH, int& firstScore, int& secondScore, int& movingPlayer) {
	Mix_Chunk* DICE = Mix_LoadWAV("kubik.mp3");
	int W, H, first_steps = 0, second_steps = 0, record = 100000;
	//rect[4] = { blueX0, blueY0, rect[4].w, rect[4].h }; // bluechip
	//rect[5] = { redX0, redY0, rect[5].w, rect[5].h }; //redchip
	drawMovingPlayer(renderer, surface, texture, rect, movingPlayer, map);
	bool quit = false, wr = false;
	SDL_Event event;

	FILE* rec = fopen("record.txt", "r");
	fseek(rec, 0, SEEK_END);
	long pos = ftell(rec);
	if (pos != 0) {
		fseek(rec, 0, SEEK_SET);
		fscanf(rec, "%d", &record);
	}
	fclose(rec);

	while (!quit){
		while (SDL_PollEvent(&event)) {
			//SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
			if (firstScore == 100 || secondScore == 100) {
				if (firstScore == 100) {
					surface = SDL_LoadBMP("firstplayerwin.bmp");
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_DestroyTexture(texture);
					SDL_RenderPresent(renderer);
					if (wr == false && first_steps < record) {
						rec = fopen("record.txt", "w");
						fprintf(rec, "%d", first_steps);
						wr = true;
						fclose(rec);
					}
				}
				else {
					surface = SDL_LoadBMP("secondplayerwin.bmp");
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_DestroyTexture(texture);
					SDL_RenderPresent(renderer);
					if (wr == false && second_steps < record) {
						rec = fopen("record.txt", "w");
						fprintf(rec, "%d", second_steps);
						wr = true;
						fclose(rec);
					}
				}
				if (event.type == SDL_MOUSEBUTTONUP)
					if (event.button.x >= rect[3].x && event.button.x <= rect[3].x + rect[3].w && event.button.y >= rect[3].y && event.button.y <= rect[3].y + rect[6].h) { 
						Mix_FreeChunk(DICE);
						cout << "first: " << first_steps << endl;
						cout << "second: " << second_steps << endl;
						fclose(rec);
						quit = true; 
					}
			}
			switch (event.type) {
			case SDL_QUIT: { saveFile(rect[4].x, rect[4].y, rect[5].x, rect[5].y, firstScore, secondScore, movingPlayer, map); exit(0); } break;
			case SDL_KEYUP: {
				if (event.key.keysym.sym == SDLK_ESCAPE) { saveFile(rect[4].x, rect[4].y, rect[5].x, rect[5].y, firstScore, secondScore, movingPlayer, map); Mix_FreeChunk(DICE); quit = true; }
				else { break; }
			} break;
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					switch (map) {
					case 1: surface = SDL_LoadBMP("map1.bmp"); break;
					case 2: surface = SDL_LoadBMP("map2.bmp"); break;
					case 3: surface = SDL_LoadBMP("map3.bmp"); break; 
					default: break;
					}
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_RenderPresent(renderer);
					SDL_DestroyTexture(texture);
					beforeW = newW, beforeH = newH;
					SDL_GetWindowSize(window, &W, &H);
					newW = W, newH = H;
					resizeRects(window, rect, beforeW, beforeH, newW, newH, blueX0, blueY0, redX0, redY0);
					drawMovingPlayer(renderer, surface, texture, rect, movingPlayer, map);
				}
				else { break; }
			} break;
			case SDL_MOUSEBUTTONUP: { 
				if (event.button.x >= rect[6].x && event.button.x <= rect[6].x + rect[6].w && event.button.y >= rect[6].y && event.button.y <= rect[6].y + rect[6].h) {
					//SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
					Mix_PlayChannel(-1, DICE, 0);
					switch (movingPlayer) {
					case 1: chipMoving(window, renderer, surface, texture, rect, movingPlayer, firstScore, map, beforeW, beforeH, newW, newH); break;
					case 2: chipMoving(window, renderer, surface, texture, rect, movingPlayer, secondScore, map, beforeW, beforeH, newW, newH); break;
					}

					if (movingPlayer == 1) {
						movingPlayer = 2;
						first_steps++;
					}
					else { 
						movingPlayer = 1;
						second_steps++;
					}

					drawMovingPlayer(renderer, surface, texture, rect, movingPlayer, map);

				}
			} break;
			default: break;
			}
		}
	}
}

void initGame(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map, int& blueX0, int& blueY0, int& redX0, int& redY0, int& beforeW, int& beforeH, float& newW, float& newH, int& firstScore, int& secondScore, int& movingPlayer) {
	SDL_RenderClear(renderer);
	switch (map) {
	case 1:  surface = SDL_LoadBMP("map1.bmp");  break;
	case 2:  surface = SDL_LoadBMP("map2.bmp");  break;
	case 3:  surface = SDL_LoadBMP("map3.bmp");  break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL); 
	SDL_DestroyTexture(texture);
	
	game(window, renderer, surface, texture, rect, 1, blueX0, blueY0, redX0, redY0, beforeW, beforeH, newW, newH, firstScore, secondScore, movingPlayer);
}

//void drawChips(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
//	surface = SDL_LoadBMP("bluechip_scaled.bmp");
//	texture = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_RenderCopy(renderer, texture, NULL, &rect[4]);
//	SDL_DestroyTexture(texture);
//	surface = SDL_LoadBMP("redchip_scaled.bmp");
//	texture = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_FreeSurface(surface);
//	SDL_RenderCopy(renderer, texture, NULL, &rect[5]);
//	SDL_RenderPresent(renderer);
//	SDL_DestroyTexture(texture);
//}

void drawMovingPlayer(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int player, int map) {
	switch (map) {
	case 1: surface = SDL_LoadBMP("map1.bmp"); break;
	case 2: surface = SDL_LoadBMP("map2.bmp"); break;
	case 3: surface = SDL_LoadBMP("map3.bmp"); break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, &rect[15] , &rect[14]);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	switch (player) {
	case 1: surface = SDL_LoadBMP("firstplayer_move.bmp"); break;
	case 2: surface = SDL_LoadBMP("secondplayer_move.bmp"); break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[6]);
	SDL_DestroyTexture(texture);
	surface = SDL_LoadBMP("bluechip_scaled.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[4]);
	SDL_DestroyTexture(texture);
	surface = SDL_LoadBMP("redchip_scaled.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[5]);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
}

void chipMoving(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int movingPlayer, int& playerScore, int map, int beforeW, int beforeH, float newW, float newH) {
	int randomArray[6], random = 0, chip, tmp, WIDTH, HEIGHT;

	switch (movingPlayer) {
	case 1: { chip = 4; } break; //blue
	case 2: { chip = 5; } break; //red
	default: break;
	} 

	for (int j = 0; j < 6; j++) {
		randomArray[j] = j + 1;
	}

	for (int i = 5; i >= 0; i--) {
		random = rand() % (i + 1);
		tmp = randomArray[i];
		randomArray[i] = randomArray[random];
		randomArray[random] = tmp;
	}

	surface = SDL_LoadBMP("dice.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	for (int j = 0; j < 3; j++) {

		for (int i = 5; i >= 0; i--) {
			random = rand() % (i + 1);
			tmp = randomArray[i];
			randomArray[i] = randomArray[random];
			randomArray[random] = tmp;
		}

		for (int i = 0; i < 6; i++) {
			random = randomArray[i];
			switch (random) {
			case 1: { SDL_RenderCopy(renderer, texture, &rect[8], &rect[7]); SDL_RenderPresent(renderer); } break;
			case 2: { SDL_RenderCopy(renderer, texture, &rect[9], &rect[7]); SDL_RenderPresent(renderer); } break;
			case 3: { SDL_RenderCopy(renderer, texture, &rect[10], &rect[7]); SDL_RenderPresent(renderer); } break;
			case 4: { SDL_RenderCopy(renderer, texture, &rect[11], &rect[7]); SDL_RenderPresent(renderer); } break;
			case 5: { SDL_RenderCopy(renderer, texture, &rect[12], &rect[7]); SDL_RenderPresent(renderer); } break;
			case 6: { SDL_RenderCopy(renderer, texture, &rect[13], &rect[7]); SDL_RenderPresent(renderer); } break;
			default: break;
			}
			SDL_Delay(100);
		}
	}
	SDL_DestroyTexture(texture);

	if (playerScore + randomArray[5] > 100) {
		return;
	}

	if (playerScore + randomArray[5] == 100) {
		rect[chip] = { rect[chip].x - int((100 * (newW / 1200)) * randomArray[5]), rect[chip].y, rect[chip].w, rect[chip].h };
		playerScore += randomArray[5];
		drawMovingPlayer(renderer, surface, texture, rect, movingPlayer, map);
		return;
	}

	for (int i = randomArray[5]; i > 0; i--) {

		if (playerScore == 10) {
			switch (chip) {
			case 4: rect[chip] = { int(917 * (newW / 1200)), int(796 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(964 * (newW / 1200)), int(796 * (newH / 1000)), rect[chip].w, rect[chip].h };  break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 20) {
			switch (chip) {
			case 4: rect[chip] = { int(18 * (newW / 1200)), int(701 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(71 * (newW / 1200)),  int(701 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 30) {
			switch (chip) {
			case 4: rect[chip] = { int(918 * (newW / 1200)), int(602 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(970 * (newW / 1200)), int(602 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 40) {
			switch (chip) {
			case 4: rect[chip] = { int(18 * (newW / 1200)), int(505 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(70 * (newW / 1200)), int(505 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 50) {
			switch (chip) {
			case 4: rect[chip] = { int(917 * (newW / 1200)), int(408 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(970 * (newW / 1200)), int(408 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 60) {
			switch (chip) {
			case 4: rect[chip] = { int(19 * (newW / 1200)), int(311 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(72 * (newW / 1200)), int(311 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 70) {
			switch (chip) {
			case 4: rect[chip] = { int(918 * (newW / 1200)), int(212 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(971 * (newW / 1200)), int(212 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 80) {
			switch (chip) {
			case 4: rect[chip] = { int(18 * (newW / 1200)), int(116 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(71 * (newW / 1200)), int(116 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 90) {
			switch (chip) {
			case 4: rect[chip] = { int(917 * (newW / 1200)), int(18 * (newH / 1000)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(970 * (newW / 1200)), int(18 * (newH / 1000)) , rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 1 && playerScore + 1 <= 10) {
			rect[chip] = { rect[chip].x + int(100 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 11 && playerScore + 1 <= 20) {
			rect[chip] = { rect[chip].x - int(100 * (newW / 1200)), rect[chip].y , rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 21 && playerScore + 1 <= 30) {
			rect[chip] = { rect[chip].x + int(99 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 31 && playerScore + 1 <= 40) {
			rect[chip] = { rect[chip].x - int(100 * (newW / 1200)) , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 41 && playerScore + 1 <= 50) {
			rect[chip] = { rect[chip].x + int(101 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 51 && playerScore + 1 <= 60) {
			rect[chip] = { rect[chip].x - int(101 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 61 && playerScore + 1 <= 70) {
			rect[chip] = { rect[chip].x + int(100 * (newW / 1200)) , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 71 && playerScore + 1 <= 80) {
			rect[chip] = { rect[chip].x - int(100 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 81 && playerScore + 1 <= 90) {
			rect[chip] = { rect[chip].x + int(100 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 91 && playerScore + 1 <= 100) {
			rect[chip] = { rect[chip].x - int(101 * (newW / 1200)), rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}
	}

	switch (map) {
	case 1: {
		if (playerScore == 2)
			if (chip == 4) {
				rect[chip] = { int(622 * (newW / 1200)), int(797 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 14;
				break;
			}
			else {
				rect[chip] = { int(672 * (newW / 1200)), int(797 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 14;
				break;
			}
		if (playerScore == 21)
			if (chip == 4) {
				rect[chip] = { int(21 * (newW / 1200)), int(506 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 41;
				break;
			}
			else {
				rect[chip] = { int(69 * (newW / 1200)), int(506 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 41;
				break;
			}
		if (playerScore == 31)
			if (chip == 4) {
				rect[chip] = { int(918 * (newW / 1200)), int(505 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 50;
				break;
			}
			else {
				rect[chip] = { int(968 * (newW / 1200)), int(505 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 50;
				break;
			}
		if (playerScore == 32)
			if (chip == 4) {
				rect[chip] = { int(718 * (newW / 1200)), int(894 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 8;
				break;
			}
			else {
				rect[chip] = { int(768 * (newW / 1200)), int(894 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 8;
				break;
			}
		if (playerScore == 42)
			if (chip == 4) {
				rect[chip] = { int(422 * (newW / 1200)), int(603 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 36;
				break;
			}
			else {
				rect[chip] = { int(482 * (newW / 1200)), int(603 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 36;
				break;
			}
		if (playerScore == 54)
			if (chip == 4) {
				rect[chip] = { int(717 * (newW / 1200)), int(212 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 73;
				break;
			}
			else {
				rect[chip] = { int(787 * (newW / 1200)), int(212 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 73;
				break;
			}
		if (playerScore == 63)
			if (chip == 4) {
				rect[chip] = { int(220 * (newW / 1200)), int(117 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 83;
				break;
			}
			else {
				rect[chip] = { int(280 * (newW / 1200)), int(117 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 83;
				break;
			}
		if (playerScore == 88)
			if (chip == 4) {
				rect[chip] = { int(824 * (newW / 1200)), int(311 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 69;
				break;
			}
			else {
				rect[chip] = { int(884 * (newW / 1200)), int(311 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 69;
				break;
			}
		if (playerScore == 99)
			if (chip == 4) {
				rect[chip] = { int(114 * (newW / 1200)), int(310 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 62;
				break;
			}
			else {
				rect[chip] = { int(174 * (newW / 1200)), int(310 * (newH / 1000)), rect[chip].w, rect[chip].h };
				playerScore = 62;
				break;
			}
	} break;
	default: break;
	}

	SDL_Delay(600);
}

void saveFile(int blueX, int blueY, int redX, int redY, int firstScore, int secondScore, int movingPlayer, int map) {
	FILE* f = fopen("save.txt", "w");
	fprintf(f, "%d %d %d %d %d %d %d %d", blueX, blueY, redX, redY, firstScore, secondScore, movingPlayer, map);
	fclose(f);
}

void loadFile(int& blueX, int& blueY, int& redX, int& redY, int& firstScore, int& secondScore, int& movingPlayer, int& map) {
	FILE* f = fopen("save.txt", "r");
	fscanf(f, "%d %d %d %d %d %d %d %d", &blueX, &blueY, &redX, &redY, &firstScore, &secondScore, &movingPlayer, &map);
	fclose(f);
}