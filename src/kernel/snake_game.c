#include "uint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

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

struct Body {
    uint32_t x, y;
    uint8_t c;
} typedef Body;

struct Snake {
    Body body[1024];
    uint32_t x, y;
    uint32_t lenght;
    uint8_t last_dep_key;
} typedef Snake;

struct Apple {
    uint32_t x, y;
    uint8_t c;
} typedef Apple;

struct period_atr_func {
    Snake *snake;
    uint8_t *map;
    Apple *apple;
} typedef period_atr_func;

int print_map(uint8_t *map);
int init_map(uint8_t *map);
int init_snake(Snake *snake);
int init_snake_on_map(uint8_t *map, Snake snake);
int init_apple_on_map(uint8_t *map, Apple apple);
void movement_snake(void *atr);
int gen_body(Snake *snake);

int snake_main(void) {
    Snake snake = {0}; 
    uint8_t map[maxY*maxX] = {0};
    Apple apple = {0};
    period_atr_func atr = {0};
    atr.map = map;
    atr.snake = &snake;
    atr.apple = &apple;

    apple.x = p_random(1, 99);
    apple.y = p_random(1, 99);
    apple.c = symbole_apple_code;
    clear_screen();
    set_cursor_pos(-1, -1);
    init_snake(&snake);
    init_map(map);
    init_snake_on_map(map, snake);
    init_apple_on_map(map, apple);
    print_map(map);
    
    set_periodic_func(&movement_snake, (void*)&atr);

    uint8_t res = 1;
    while(1){
        check_periodic_func(&movement_snake, &res);
        if (!res){
            break;
        }
    }
    clear_screen();
    return 0;
}

int init_apple_on_map(uint8_t *map, Apple apple) {
    map[apple.y * maxX + apple.x] = apple.c;
}

int init_snake(Snake *snake) {
    memset((uint8_t*)snake, 0, sizeof(snake));
    
    snake->x = 10;
    snake->y = 10;
    snake->last_dep_key = 0;
    snake->lenght = 3;
    snake->body[0].x = 9;
    snake->body[0].y = 10;
    snake->body[0].c = symbole_body_snake_code;
    snake->body[1].x = 8;
    snake->body[1].y = 10;
    snake->body[1].c = symbole_body_snake_code;
    snake->body[2].x = 7;
    snake->body[2].y = 10;
    snake->body[2].c = symbole_body_snake_code;

    snake->body[3].x = 0;
    snake->body[3].y = 0;
    snake->body[3].c = 0;
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

int init_snake_on_map(uint8_t *map, Snake snake) {
    for (int i = 0; i < snake.lenght; i++) {
        if ((snake.body->c) == symbole_body_snake_code) {
            map[snake.body[i].y * maxX + snake.body[i].x] = symbole_body_snake_code;
        }
        else if ((snake.body->c) == 0) {
            break;
        }
    }

    map[snake.y * maxX + snake.x] = symbole_head_snake_code;
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

void movement_snake(void *a) {
    period_atr_func *atr = (period_atr_func*)a;
    uint8_t key = 0;
    uint8_t *map = atr->map;
    Snake *snake = atr->snake;
    Body *body = snake->body;
    Apple *apple = atr->apple;
    scan(&key);
    if (key != 0 || snake->last_dep_key != 0) {
        for (int i = 0; i < snake->lenght; i++) {
            map[(body+i)->y * maxX + (body+i)->x] = symbole_void_code;
        }
        map[snake->y * maxX + snake->x] = symbole_void_code;

        for (int i = snake->lenght - 1; i > 0; i--) {
            (body + i)->x = (body + i - 1)->x;
            (body + i)->y = (body + i - 1)->y;
        }
        body->x = snake->x;
        body->y = snake->y;
    }

    if (key == 'w' && snake->last_dep_key != 's') {
        (snake->y) = snake->y - 1;
        snake->last_dep_key = 'w';
    }
    else if (key == 'a' && snake->last_dep_key != 'd') {
        (snake->x) = snake->x - 1;
        snake->last_dep_key = 'a';
    }
    else if (key == 'd' && snake->last_dep_key != 'a') {
        (snake->x) = snake->x + 1;
        snake->last_dep_key = 'd';
    }
    else if (key == 's' && snake->last_dep_key != 'w') {
        (snake->y) = snake->y + 1;
        snake->last_dep_key = 's';
    }
    if (key == '\0') {   
        if (snake->last_dep_key == 'w') {
            (snake->y) = snake->y - 1;
        }
        else if (snake->last_dep_key == 'a') {
            (snake->x) = snake->x - 1;
        }
        else if (snake->last_dep_key == 'd') {
            (snake->x) = snake->x + 1;
        }
        else if (snake->last_dep_key == 's') {
            (snake->y) = snake->y + 1;
        }
    }
    
    if (snake->x == apple->x && snake->y == apple->y) {
        int rand = p_random(1, 99);
        apple->x = p_random(1, 99) < 1 ? 20: rand;
        apple->y = p_random(1, 99) < 1 ? 35: p_random(1, 99);
        init_apple_on_map(map, *apple);
        gen_body(snake);
    }

    if (snake->x == 0 || snake->x == maxX || snake->y == 0 || snake->y == maxY) {
        del_periodic_func();
    }
    init_snake_on_map(map, *snake);
    print_map(map);
}

int gen_body(Snake *snake) {
    int lenght = snake->lenght + 1;
    Body *body = snake->body;
    (body + lenght)->x = (body + lenght - 1)->x;
    (body + lenght)->y = (body + lenght - 1)->y;
    snake->lenght++;
}
