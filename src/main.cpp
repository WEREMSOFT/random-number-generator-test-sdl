#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>
#define WIDTH 640
#define HEIGHT 480
int columnHeihgt[WIDTH] = {0};


uint32_t pcgHash(uint32_t input)
{
	uint state = input * 747796405u + 2891336453u;
	uint word  = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return (word >> 22u) ^ word;
}

uint32_t wangHash(uint32_t seed)
{
	seed = (seed ^ 61) ^ (seed >> 16);
	seed *= 9;
	seed = seed ^ (seed >> 4);
	seed *= 0x27d4eb2d;
	seed = seed ^ (seed >> 15);
	return seed;
}

float wangRandom(uint32_t seed)
{
	return (float)wangHash(seed) / (float)UINT32_MAX;
}

float pcgRandom(uint32_t seed)
{
	return (float)pcgHash(seed) / (float)UINT32_MAX;
}

int main(void)
{
 if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "No se pudo inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
										  //  | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        fprintf(stderr, "No se pudo crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "No se pudo crear el renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int running = 1;
	uint32_t seed = 0;
	srand((unsigned int) time(NULL));
    while (running) {
		seed++;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

		int32_t index2 = (int32_t)floor(wangRandom(seed) * WIDTH);
		// int32_t index = rand() % 640;

		// columnHeihgt[index]++;
		columnHeihgt[index2]++;

		// Dibujar píxeles usando SDL_RenderDrawPoint
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Color azul
		// SDL_RenderDrawPoint(renderer, index, 480 - columnHeihgt[index]);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Color azul
		SDL_RenderDrawPoint(renderer, index2, HEIGHT - columnHeihgt[index2]);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}