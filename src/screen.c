#include "screen.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdint.h>
#include <stdio.h>


//#define SCREEN_HEIGHT 64;
//#define SCREEN_WIDTH 32;
const int SCREEN_HEIGHT = 32;
const int SCREEN_WIDTH = 64;
const int SCALE = 10;


uint8_t display[SCREEN_HEIGHT * SCREEN_WIDTH];


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


void test_func() {
    printf("Hello from another file!\n");
    printf("And I'll do it again!\n");
}


int init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf(
            "SDL could not initialize! Error: %s\n",
            SDL_GetError()
        );
        return -1;
    }

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH * SCALE,
        SCREEN_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Window could not be created! Error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == NULL) {
        printf("Renderer could not be created! Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_RenderSetScale(renderer, SCALE, SCALE);
    return 0;
}


void clear_display() {
    memset(display, 0, sizeof(display));
}


void print_screen_matrix() {
    int display_index = 0;
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++, display_index++) {
            printf("%d ", display[display_index]);
        }
        printf("\n");
    }
}


uint8_t draw_sprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t height) {
    uint8_t collisions = 0;

    for (uint8_t row = 0; row < height; row++) {
        uint8_t pixel_row = sprite[row];

        for (uint8_t col = 0; col < 8; col++) {
            if (pixel_row & (0x80 >> col)) {
                uint8_t pixel_x = (x + col) % SCREEN_WIDTH; 
                uint8_t pixel_y = (y + row) % SCREEN_HEIGHT;
                printf("write to pixel coords: (%d, %d)\n", pixel_x, pixel_y);

                uint16_t index = pixel_x + (pixel_y * SCREEN_WIDTH);
                printf("converts to flattened index: %d\n", index);

                if (display[index]) {
                    printf("collision at: (%d, %d)\n", pixel_x, pixel_y);
                    collisions += 1;
                }

                display[index] ^= 1;
            }
        }
    }
    print_screen_matrix();
    return collisions;
}


void update_display() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 225, 225, 255, 255);

    for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
        for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
            if (display[x + y * SCREEN_WIDTH]) {
                SDL_Rect pixel = {x, y, 1, 1};
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }
    SDL_RenderPresent(renderer);
}


void cleanup_graphics() {
    printf("Cleaning up SDL resources\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
