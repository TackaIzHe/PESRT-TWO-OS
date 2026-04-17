#include "stdio.h"
#include "ash.h"
#include "string.h"

static inline int comand_list(const uint16_t comand_number, const uint8_t *arg, uint32_t cnt_str, uint32_t str_len);
static inline int convert_str_to_comand(const uint8_t *str);

static inline int echo(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int cat(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int ls(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int touch(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int mkdir(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int procedure(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);

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

static inline int convert_str_to_comand(const uint8_t *str) {
    uint8_t arg[20][200] = {0};
    uint16_t cmd = CMD_EXIT;
    strsplit((uint8_t *)arg, 200, str, 20, ' ');
    if (strcmp(arg[0], CMDSTR_ECHO) == 0) {
        cmd = CMD_ECHO;
    }
    else if (strcmp(arg[0], CMDSTR_CAT) == 0) {
        cmd = CMD_CAT;
    }
    else if (strcmp(arg[0], CMDSTR_LS) == 0) {
        cmd = CMD_LS;
    }
    else if (strcmp(arg[0], CMDSTR_MKDIR) == 0) {
        cmd = CMD_MKDIR;
    }
    else if (strcmp(arg[0], CMDSTR_TOUCH) == 0) {
        cmd = CMD_TOUCH;
    }
    else if (strcmp(arg[0], CMDSTR_EXIT) == 0) {
        cmd = CMD_EXIT;
    }
    
    comand_list(cmd, (uint8_t *)arg, 20, 200);
}

static inline int comand_list(const uint16_t comand_number, const uint8_t *arg, uint32_t cnt_str, uint32_t str_len) {
    switch (comand_number) {
        case CMD_ECHO:           return echo(arg, cnt_str, str_len);
        case CMD_CAT:            return echo(arg, cnt_str, str_len);
        case CMD_PROCEDURE:      return echo(arg, cnt_str, str_len);
        case CMD_LS:             return echo(arg, cnt_str, str_len);
        case CMD_MKDIR:          return echo(arg, cnt_str, str_len);
        case CMD_TOUCH:          return echo(arg, cnt_str, str_len);
        
        case CMD_EXIT:           return CMD_EXIT;
        default:                 return CMD_EXIT;
    }
}

static inline int echo(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {
    printf("echo");
}
static inline int cat(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int ls(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int touch(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int mkdir(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int procedure(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}