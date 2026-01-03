#include "screen.h"
#include <SDL.h>
#include <stdio.h>

#define SCREEN_HEIGHT = 64;
#define SCREEN_WIDTH = 32;
#define SCALE = 10;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void test_func() {
    printf("Hello from another file!\n");
}
