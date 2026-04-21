#include "stdio.h"
#include "ash.h"
#include "string.h"
#include "video_driver/pci.h"
#include "video_driver/vbe.h"

static inline int comand_list(const uint16_t comand_number, const uint8_t *arg, uint32_t cnt_str, uint32_t str_len);
static inline int convert_str_to_comand(const uint8_t *str);

static inline int echo(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int cat(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int ls(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int touch(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int mkdir(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int procedure(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int lspci(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);
static inline int cgpu(const uint8_t *str, uint32_t cnt_str, uint32_t str_len);

int ash_main(void) {
    uint8_t buffer[1024] = {0};
    uint8_t input_buffer[512] = {0};
    strcpy(buffer, USER_LINE);
    sprintf(buffer, buffer, "user qwe 52");
    while (1) {
        printf(buffer);
        scanf(input_buffer);
        convert_str_to_comand(input_buffer);
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
    else if (strcmp(arg[0], CMDSTR_LSPCI) == 0) {
        cmd = CMD_LSPCI;
    }
    else if (strcmp(arg[0], CMDSTR_CGPU) == 0) {
        cmd = CMD_CGPU;
    }
    else if (strcmp(arg[0], CMDSTR_EXIT) == 0) {
        cmd = CMD_EXIT;
    }
    
    comand_list(cmd, (uint8_t *)arg, 20, 200);
}

static inline int comand_list(const uint16_t comand_number, const uint8_t *arg, uint32_t cnt_str, uint32_t str_len) {
    switch (comand_number) {
        case CMD_ECHO:           return echo(arg, cnt_str, str_len);
        case CMD_CAT:            return cat(arg, cnt_str, str_len);
        case CMD_PROCEDURE:      return echo(arg, cnt_str, str_len);
        case CMD_LS:             return echo(arg, cnt_str, str_len);
        case CMD_MKDIR:          return echo(arg, cnt_str, str_len);
        case CMD_TOUCH:          return echo(arg, cnt_str, str_len);
        case CMD_LSPCI:          return lspci(arg, cnt_str, str_len);
        case CMD_CGPU:           return cgpu(arg, cnt_str, str_len);
        case CMD_EXIT:           return CMD_EXIT;
        default:                 return CMD_EXIT;
    }
}

static inline int echo(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {
    printf("echo");
}
static inline int cat(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {
    // vbe_info_t *qwe = vbe_get_info();
    // printf("%d \n", qwe->version);
}
static inline int ls(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int touch(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int mkdir(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}
static inline int lspci(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {
    print_PCI_devices();
    return 0;
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    // Проверка границ (опционально)
    if (x >= 1024 || y >= 768) return;

    // Вычисляем смещение: y * pitch + x * bytes_per_pixel
    // Предположим: bpp=32 → 4 байта на пиксель
    uint32_t offset = y * 1024 * 4 + x * 4; // pitch = 1024 * 4 (если 32bpp)
    // ⚠️ ЛУЧШЕ: использовать mode_info.pitch, а не хардкодить!
    // В реальности: offset = y * pitch + x * (bpp / 8);

    // Записываем цвет (little-endian)
    // *(uint32_t*)(mode_info.framebuffer + offset) = color;
}

static inline int cgpu(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {
    uint32_t bar = check_GPU_BAR();
    uint8_t class = check_GPU_class();
    uint8_t revision_id = check_GPU_revision_id();
 
    // printf("%d %d\n", mode_info.framebuffer, mode_info.width);
    // draw_pixel(512, 384, 0xFF0000FF);
}

static inline int procedure(const uint8_t *str, uint32_t cnt_str, uint32_t str_len) {

}