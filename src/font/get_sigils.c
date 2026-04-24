#include <stdio.h>
#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>
#include <freetype2/freetype/ftimage.h>
#include <string.h>

#define HEIGHT 20
#define WEIGHT 16

// Функция для вывода битмапа символа
void print_bitmap(FT_Bitmap* bitmap, char c) {
    printf("const uint16_t sumbole_%c[] = { \\\n", c);
    for (int y = 0; y < bitmap->rows; y++) {
        printf("(uint16_t)0b");
        for (int x = 0; x < bitmap->width; x++) {
            // Проверяем, установлен ли пиксель (бит)
            if (bitmap->buffer[y * bitmap->width + x] > 0) {
                printf("1");  // Заполненный пиксель
            } else {
                printf("0");  // Пустой пиксель
            }
        }
        int a = WEIGHT - bitmap->width;
        for (int i = 0; i < a; i++)
            printf("0");

        if (y != bitmap->rows-1)
            printf(", \\\n");
    }
    
    printf(", \\\n");
    int a = HEIGHT - bitmap->rows;
    for (int i = 0; i < a; i++) {
        printf("(uint16_t)0b");
        for (int j = 0; j < WEIGHT; j++) {
            printf("0");
        }
        if (i == a - 1)
            break;
        printf(", \\\n");
    }    
    printf(" };\n");
}

int main() {
    FT_Library library;
    FT_Face face;
    char sl[] = {'~','!','@','#','$','%','^','&','*','(',')','-','_','+','=','\\',';',':','\"','\'','<','>','[',']','{','}','/','?','|','\0'};
    // Инициализация FreeType
    if (FT_Init_FreeType(&library)) {
        fprintf(stderr, "Ошибка инициализации FreeType\n");
        return 1;
    }

    // Загрузка шрифта (укажите путь к вашему TTF-файлу)
    if (FT_New_Face(library, "/home/tackaizhe/PESRT-TWO-OS/src/font/DejaVuSans.ttf", 0, &face)) {
        fprintf(stderr, "Ошибка загрузки шрифта\n");
        return 1;
    }

    // Установка размера шрифта (в пикселях)
    FT_Set_Pixel_Sizes(face, WEIGHT, HEIGHT);  // 16x16 пикселей

    // Английский алфавит (A-Z, a-z)
    printf("//=== Английский алфавит ===\n");
    for (char c = 'A'; c <= 'Z'; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, c);
        printf("\n");
    }
    for (char c = 'a'; c <= 'z'; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, c);
        printf("\n");
    }
    printf("//Цыфирки\n");
    for (char c = '0'; c <= '9'; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, c);
        printf("\n");
    }
    printf("//=== Русский алфавит ===\n");
    for (wchar_t c = L'А'; c <= L'Я'; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, c);
        printf("\n");
    }
    for (wchar_t c = L'а'; c <= L'я'; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, c);
        printf("\n");
    }
    printf("//Служебные символы\n");
    for (int c = 0; c < strlen(sl); c++) {
        char q = sl[c];
        FT_Load_Char(face, q, FT_LOAD_RENDER);
        print_bitmap(&face->glyph->bitmap, q);
        printf("\n");
    }

    // Освобождение ресурсов
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return 0;
}