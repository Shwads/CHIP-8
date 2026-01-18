#include <stdint.h>
#include <stdio.h>
#include <SDL.h>
#include "chip8.h"
#include "screen.h"


#define PC_MASK = 0x0FFFu;


uint8_t FONT[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void load_font(cpu *cpu, uint8_t start_idx, uint8_t *font_arr, uint8_t s_font_arr) {
    for (int i = start_idx, p_font_arr = 0; p_font_arr < s_font_arr; p_font_arr++) {
        cpu->MEMORY[i+p_font_arr] = font_arr[p_font_arr];
    }
}


int main() {
    printf("Initialising CHIP-8 emulator!\n");
    cpu chip8;

    uint8_t graphics = init_graphics();
    if (graphics != 0) {
        return -1;
    }

    SDL_Event event;
    uint8_t running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_0:
                        uint8_t collisions = draw_sprite(10, 10, &FONT[0], 5);
                        printf("drew sprite with: %d collisions\n", collisions);
                        update_display();
                        break;
                    case SDLK_1: break;
                    case SDLK_2: break;
                }
            }
        }
        uint32_t ticks = SDL_GetTicks();
        if (ticks % 16 == 0) {
            if (chip8.delay_timer > 0) chip8.delay_timer--;
            if (chip8.sound_timer > 0) chip8.sound_timer--;
        }
        //update_display();
    }
    cleanup_graphics();
    return 0;
}
