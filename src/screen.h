#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

void test_func();

int init_graphics();

void clear_display();

uint8_t draw_sprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t height);

void update_display();

void cleanup_graphics();

#endif
