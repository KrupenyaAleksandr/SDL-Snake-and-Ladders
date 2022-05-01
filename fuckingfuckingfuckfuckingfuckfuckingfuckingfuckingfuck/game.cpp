#include "head.h"

void game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map) {
	int player = 1, first_score = 1, second_score = 1, score = 1, tmpX, tmpY, blueX = 17, blueY = 892, redX = 64, redY = 892, beforeW = 1200, beforeH = 1000, newW = 0, newH = 0;
	drawMovingPlayer(renderer, surface, texture, rect, player, map);
	int WIDTH, HEIGHT;
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {exit(0); } break;
			case SDL_KEYUP: {
				if (event.key.keysym.sym == SDLK_ESCAPE) { quit = true; }
				else { break; }
			} break;
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					switch (map) {
					case 1: { surface = SDL_LoadBMP("map1.bmp"); } break;
					case 2: { surface = SDL_LoadBMP("map2.bmp"); } break;
					default: break;
					}
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
					SDL_RenderCopy(renderer, texture, NULL, NULL);
					SDL_RenderPresent(renderer);
					SDL_DestroyTexture(texture);
					SDL_GetWindowSize(window, &newW, &newH);
					resizeRects(window, rect, blueX, blueY, redX, redY, beforeW, beforeH, newW, newH);
					blueX = rect[4].x, blueY = rect[4].y, redX = rect[5].x, redY = rect[5].y;
					//drawChips(renderer, surface, texture, rect);
					drawMovingPlayer(renderer, surface, texture, rect, player, map);
					beforeW = newW, beforeH = newH;
				}
				else { break; }
			} break;
			case SDL_MOUSEBUTTONUP: { 
				if (event.button.x >= rect[6].x && event.button.x <= rect[6].x + rect[6].w && event.button.y >= rect[6].y && event.button.y <= rect[6].y + rect[6].h) {

					switch (player) {
					case 1: chipMoving(window, renderer, surface, texture, rect, player, first_score, map, blueX, blueY, redX, redY, beforeW, beforeH); break;
					case 2: chipMoving(window, renderer, surface, texture, rect, player, second_score, map, blueX, blueY, redX, redY, beforeW, beforeH); break;
					}

					if (player == 1) {
						player = 2;
					}
					else { player = 1; }

					drawMovingPlayer(renderer, surface, texture, rect, player, map);

					//if (flag) {
					//	player = 1;
					//	chipMoving(renderer, surface, texture, rect, player, second_score, map);
					//	flag = false;
					//}
					//else {
					//	player = 2;
					//	chipMoving(renderer, surface, texture, rect, player, first_score, map);
					//	flag = true;
					//}

					/*drawMovingPlayer(renderer, surface, texture, rect, player);*/
					/*drawChips(renderer, surface, texture, rect);*/

					cout << "bebra" << endl;
			}
			} break;
			default: break;
			}
		}
	}
}

void initGame(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int map) {
	SDL_RenderClear(renderer);
	switch (map) {
	case 1: { surface = SDL_LoadBMP("map1.bmp"); } break;
	case 2: { surface = SDL_LoadBMP("map2.bmp"); } break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL); 
	drawChips(renderer, surface, texture, rect);
	SDL_DestroyTexture(texture);
	
	game(window, renderer, surface, texture, rect, 1);
}

void drawChips(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[]) {
	surface = SDL_LoadBMP("bluechip_scaled.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[4]);
	SDL_DestroyTexture(texture);
	surface = SDL_LoadBMP("redchip_scaled.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[5]);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}

void drawMovingPlayer(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int player, int map) {
	switch (map) {
	case 1: surface = SDL_LoadBMP("map1.bmp"); break;
	case 2: surface = SDL_LoadBMP("map2.bmp"); break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, &rect[15] , &rect[14]);
	SDL_RenderPresent(renderer);
	switch (player) {
	case 1: surface = SDL_LoadBMP("firstplayer_move.bmp"); break;
	case 2: surface = SDL_LoadBMP("secondplayer_move.bmp"); break;
	default: break;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &rect[6]);
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

void chipMoving(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect rect[], int movingPlayer, int& playerScore, int map, int& blueX, int& blueY, int& redX, int& redY, int beforeW, int beforeH) {
	int randomArray[6], random = 0, tmp, chip, tmpNextStroka = 1, nextStroka = 1, WIDTH, HEIGHT;
	float newW, newH;
	bool changeY = true;

	SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
	newW = WIDTH; newH = HEIGHT;

	switch (movingPlayer) {
	case 1: { chip = 4; } break;
	case 2: { chip = 5; } break;
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

	for (int i = randomArray[5]; i > 0; i--) {

		if (playerScore + randomArray[5] > 100) {
			return;
		}

		//if (playerScore == 10) {
		//	switch (chip) {
		//	case 4: rect[chip] = { int(917 * (tmpWIDTH / 1200)), int(796 * (tmpHEIGHT / 1000)), rect[chip].w, rect[chip].h }; break;
		//	case 5: rect[chip] = { int(964 * (tmpWIDTH / 1200)), int(796 * (tmpHEIGHT / 1000)), rect[chip].w, rect[chip].h };  break;
		//	}
		//	playerScore++; 
		//	continue;
		//}

		if (playerScore == 10) {
			switch (chip) {
			case 4: rect[chip] = { int(917 * (newW / beforeW)), int(796 * (newH / beforeH)), rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { int(964 * (newW / beforeW)), int(796 * (newH / beforeH)), rect[chip].w, rect[chip].h };  break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 20) {
			switch (chip) {
			case 4: rect[chip] = { 18, 701, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 71, 701, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 30) {
			switch (chip) {
			case 4: rect[chip] = { 918, 602, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 970, 602, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 40) {
			switch (chip) {
			case 4: rect[chip] = { 18, 505, rect[chip].w, rect[chip].h }; break; 
			case 5: rect[chip] = { 70, 505, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 50) {
			switch (chip) {
			case 4: rect[chip] = { 917, 408, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 970, 408, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 60) {
			switch (chip) {
			case 4: rect[chip] = { 19, 311, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 72, 311, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 70) {
			switch (chip) {
			case 4: rect[chip] = { 918, 212, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 971, 212, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 80) {
			switch (chip) {
			case 4: rect[chip] = { 18, 116, rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 71, 116, rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore == 90) {
			switch (chip) {
			case 4: rect[chip] = { 917, 18 , rect[chip].w, rect[chip].h }; break;
			case 5: rect[chip] = { 970, 18 , rect[chip].w, rect[chip].h }; break;
			}
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 1 && playerScore + 1 <= 10) {
			if (chip == 4) {
				blueX = rect[chip].x + int(100 * (newW / beforeW));
				//if (changeY) {
				//	/*blueY = int(rect[chip].y * (tmpHEIGHT / 1000));*/
				//	blueY = int(rect[chip].y * (newH / beforeH));
				//	changeY = false;
				//}
				rect[chip] = { blueX, rect[chip].y, rect[chip].w, rect[chip].h };
			}
			else {
				redX = rect[chip].x + int(100 * (newW / beforeW));
				//if (changeY) {
				//	/*redY = int(rect[chip].y * (tmpHEIGHT / 1000));*/
				//	redY = int(rect[chip].y * (newH / beforeH));
				//	changeY = false;
				//}
				rect[chip] = { redX, rect[chip].y, rect[chip].w, rect[chip].h };
			}
			/*rect[chip] = { blueX, rect[chip].y, rect[chip].w, rect[chip].h };*/
			playerScore++;
			continue;
		}

		// вроде бы нормальный вариант, надо ещё чёто потыкать хз завтра разберёмся 

		//if (playerScore + 1 >= 1 && playerScore + 1 <= 10) {
		//	rect[chip] = { rect[chip].x + int(100 * (newW / beforeW)), int(rect[chip].y * (newH / beforeH)), rect[chip].w, rect[chip].h };
		//	playerScore++;
		//	continue;
		//}

		if (playerScore + 1 >= 11 && playerScore + 1 <= 20) {
			rect[chip] = { rect[chip].x - int(100 * (newW / beforeW)), int(rect[chip].y * (newH / beforeH)), rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 21 && playerScore + 1 <= 30) {
			rect[chip] = { rect[chip].x + 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 31 && playerScore + 1 <= 40) {
			rect[chip] = { rect[chip].x - 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 41 && playerScore + 1 <= 50) {
			rect[chip] = { rect[chip].x + 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 51 && playerScore + 1 <= 60) {
			rect[chip] = { rect[chip].x - 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 61 && playerScore + 1 <= 70) {
			rect[chip] = { rect[chip].x + 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 71 && playerScore + 1 <= 80) {
			rect[chip] = { rect[chip].x - 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 81 && playerScore + 1 <= 90) {
			rect[chip] = { rect[chip].x + 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}

		if (playerScore + 1 >= 91 && playerScore + 1 <= 100) {
			rect[chip] = { rect[chip].x - 100 , rect[chip].y, rect[chip].w, rect[chip].h };
			playerScore++;
			continue;
		}
	}
}