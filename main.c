#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exit_sdl(char *msg) {
	printf("%s: %s\n", msg, SDL_GetError());
	exit(1);
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != true)
		exit_sdl("Unable to Init SDL");

	srand(time(NULL));
	atexit(SDL_Quit);
	uint32_t win_hei = 800, win_wid = 1200;
	//SDL_WM_SetCaption("Tessst", "Teeest");
	//SDL_Surface *screen = SDL_SetVideoMode(1200, 800, 0, 0);
	SDL_Window *win = SDL_CreateWindow("teteest", win_wid, win_hei,
			SDL_WINDOW_RESIZABLE|
			SDL_WINDOW_ALWAYS_ON_TOP);

	if (!win)
		exit_sdl("can't create SDL window");

	SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);

	if (!ren)
		exit_sdl("can't create SDL renderer");


	SDL_Event event;
	int gameover = 0, key;
	int count = win_hei*win_wid;
	SDL_FPoint points[count];

	for (int y = 0, pIndex = 0; y < win_hei; y++) 
		for (int x = 0; x < win_wid; x++) { 
			points[pIndex].x = x;
			points[pIndex++].y = y;
		}


	while (!gameover) {
		if (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_EVENT_QUIT:
					gameover = 1;
					break;
				case SDL_EVENT_KEY_DOWN:
					key = event.key.key;
					switch (key)	 {
						case SDLK_ESCAPE:
							key = SDLK_Q;
						case SDLK_Q:
							gameover = 1;
							break;
						dafault:	break;
					}
					break;
			}
		}

		SDL_SetRenderDrawColor(ren,
			rand() % 0xFF,
			rand() % 0xFF,
			rand() % 0xFF, 0xFF);

		SDL_RenderPoints(ren, points, count);
		SDL_RenderPresent(ren);
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}
