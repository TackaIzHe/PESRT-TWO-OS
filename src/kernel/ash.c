#include "stdio.h"
#include "ash.h"
#include "string.h"

static inline int comand_list(const uint16_t comand_number, const uint8_t **arg);
static inline int convert_str_to_comand(const uint8_t *str);
static inline int echo(const uint8_t **str);

int ash_main(void) {
    uint8_t buffer[1024] = {0};
    uint8_t input_buffer[512] = {0};
    strcpy(buffer, USER_LINE);
    sprintf(buffer, buffer, "user qwe 52");
    while (1) {
        printf(buffer);
        scanf(input_buffer);
        convert_str_to_comand(input_buffer);
        // if (comand_list(input_buffer) == EXIT)
    }
}

static inline int echo(const uint8_t **str) {

}

static inline int convert_str_to_comand(const uint8_t *str) {
    uint8_t arg[20][200] = {0};
    strsplit((uint8_t *)arg, 200, str, 20, ' ');
    printf("%s\n", arg[0]);
    printf("%s\n", arg[1]);
    printf("%s\n", arg[2]);
}

static inline int comand_list(const uint16_t comand_number, const uint8_t **arg) {
    switch (comand_number) {
        case 0:          return echo(arg);
        default:         return EXIT;
    }
}