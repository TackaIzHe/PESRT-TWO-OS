#include "uint.h"
#include "stdio.h"

struct Player {
    int x, y, xp;
    char playerSymbol;
} typedef Player;

#define maxX 100
#define maxY 100

enum {
    symbole_void_code       = 0,
    symbole_head_snake_code = 1,
    symbole_body_snake_code,
    symbole_wall_left_code,
    symbole_wall_up_code,
    symbole_wall_down_code,
    symbole_wall_right_code,
    symbole_apple_code,
};

uint16_t symbole_head_snake[] = {
    (uint16_t)0b0010000100,
    (uint16_t)0b0011111100,
    (uint16_t)0b0010110100,
    (uint16_t)0b0011111100,
    (uint16_t)0b0010110100,
    (uint16_t)0b0010000100,
    (uint16_t)0b0010000100,
    (uint16_t)0b0011111100,
    (uint16_t)0b0010000100,
    (uint16_t)0b0010000100
};

uint16_t symbole_body_snake[] = {
    (uint16_t)0b0000000000,
    (uint16_t)0b0111111110,
    (uint16_t)0b0100000010,
    (uint16_t)0b0100000010,
    (uint16_t)0b0111111110,
    (uint16_t)0b0100000010,
    (uint16_t)0b0100000010,
    (uint16_t)0b0100000010,
    (uint16_t)0b0111111110,
    (uint16_t)0b0000000000
};

uint16_t symbole_wall_left[] = {
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101,
    (uint16_t)0b0000000101
};

uint16_t symbole_wall_up[] = {
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b1111111111,
    (uint16_t)0b0000000000,
    (uint16_t)0b1111111111
};

uint16_t symbole_wall_down[] = {
    (uint16_t)0b1111111111,
    (uint16_t)0b0000000000,
    (uint16_t)0b1111111111,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000,
    (uint16_t)0b0000000000
};

uint16_t symbole_wall_right[] = {
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000,
    (uint16_t)0b101000000
};

const uint16_t symbole_apple[] = {
    (uint16_t)0b0000000000,
    (uint16_t)0b0111111110,
    (uint16_t)0b0100110010,
    (uint16_t)0b0100110010,
    (uint16_t)0b0111111110,
    (uint16_t)0b0100110010,
    (uint16_t)0b0100110010,
    (uint16_t)0b0100110010,
    (uint16_t)0b0111111110,
    (uint16_t)0b0000000000
};

const uint16_t symbole_void[] = {
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0,
    (uint16_t)0b0
};

static const uint16_t* get_buffer(char symbol) {
    switch (symbol) {
        case symbole_apple_code:      return symbole_apple;
        case symbole_body_snake_code: return symbole_body_snake;
        case symbole_head_snake_code: return symbole_head_snake;
        case symbole_void_code:       return symbole_void;
        case symbole_wall_down_code:  return symbole_wall_down;
        case symbole_wall_left_code:  return symbole_wall_left;
        case symbole_wall_right_code: return symbole_wall_right;
        case symbole_wall_up_code:    return symbole_wall_up;
        default:                      return symbole_void;
    }
}


int print_map(uint8_t *map);
int init_map(uint8_t *map);

int snake_main(void) {
    uint8_t map[maxY*maxX] = {0};
    clear_screen();
    set_cursor_pos(-1, -1);
    init_map(map);
    print_map(map);
    

    while(1){}
    return 0;
}

int init_map(uint8_t *map) {
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            if (i == 0) {
                map[i*maxX+j] = symbole_wall_up_code;
                continue;
            }
            else if (j == 0) {
                map[i*maxX+j] = symbole_wall_left_code;
                continue;
            }
            else if (j == maxX-1) {
                map[i*maxX+j] = symbole_wall_right_code;
                continue;
            }
            else if (i == maxY-1) {
                map[i*maxX+j] = symbole_wall_down_code;
                continue;
            }
            map[i*maxX+j] = symbole_void_code;
        }
    }
    return 0;
}

int print_map(uint8_t *map) {
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            const uint16_t* buffer = get_buffer(map[i*maxX+j]);
            print_pixels_array(buffer, j, i, 10,10);
        }
    }
    
    return 0;
}

int movement_snake(void) {
    return 0;
}

int gen_apple(void) {
    return 0;
}

