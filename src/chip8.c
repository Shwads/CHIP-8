#include <stdint.h>

uint8_t MEMORY[4096];
uint16_t PC;
uint16_t I;

uint8_t sound_timer;
uint8_t delay_timer;

uint8_t registers[16];

typedef struct {
    int top;
    uint16_t vals[50];
} stack;
