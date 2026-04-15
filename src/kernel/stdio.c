#include "uint.h"
#include "stdio.h"
#include "interapts/interapt.h"
#include "string.h"

uint8_t press_key = 0;
uint16_t* cursor_pos = 0;
uint8_t cursor_offset = 0;
uint8_t terminal_tem = ((BLACK << 4) | WHITE);
uint8_t user_line[255] = "<PESRT-TWO-OS>[_] /";

static inline uint8_t sumbole_down_convert(uint8_t sumb);
static inline uint8_t sumbole_up_convert(uint8_t sumb);

void scan_key(void) {
    
    while(press_key == 0) {
        __asm__ __volatile__ ("int $0x21");
        __asm__ __volatile__ ("hlt");
    }
    press_key = sumbole_down_convert(press_key);
    if (press_key != '\0'){
        uint16_t* vm = (uint16_t*)0xb8000;
        vm[1] = 0x0F << 8 | press_key;
    }
    press_key = 0;

}

void clear_screen(uint32_t x, uint32_t y) {
    uint16_t *start = (uint16_t*)START_VIDEO_MEM;
    for (uint32_t i = 0; i < y * x; i++)
        *(start + i) = (terminal_tem << 8) | 0;
}
void init_cursor_pos(void) {
    cursor_pos = (uint16_t *)START_VIDEO_MEM;
}

void set_terminal_tem(uint8_t background, uint8_t text_color) {
    terminal_tem = ((background << 4) | text_color);
}

void printf(const uint8_t *str, const uint32_t *arg) {
    uint8_t buffer[1024];
    sprintf(buffer, str, arg);
    uint32_t len = strlen(buffer);
    for (uint32_t i = 0; i < len; i++) {
        *cursor_pos = (terminal_tem << 8) | buffer[i];
        cursor_pos++;
    }
}

void sprintf(uint8_t *dest, const uint8_t *str, const uint32_t *arg) {
    uint8_t buffer[1024];
    uint32_t cur_arg = 0;
    strcpy(buffer, str);
    uint32_t len = strlen(buffer);
    for (uint32_t i = 0; i < len; i++) {
        if (buffer[i] == '%') {
            switch (buffer[i+1]) {
                case 'c': {
                    buffer[i] = arg[cur_arg];
                    cur_arg++;
                    i++;
                    for (int j = i; j < len; j++) {
                        buffer[j] = buffer[j + 1];
                    }
                    len--;
                    continue;
                    break;
                }
                case 'd': {
                    uint8_t int_str[15];
                    uint8_t rigth_half[1024];
                    convert_int_to_string(arg[cur_arg], int_str);
                    strcpy(rigth_half, buffer + i);
                    strcpy(buffer + i, int_str);
                    uint32_t new_len = strlen(int_str) + i;
                    strcmp(buffer + new_len, rigth_half);
                    break;
                }
                case 's': {
                    break;
                }
            }
        }
    }
    len = strlen(buffer);
    strcpy(dest, buffer);
}

void scanf(uint8_t *buff) {

}

void convert_int_to_string(uint32_t num, uint8_t *buff) {
    uint32_t ostatok = num;
    uint32_t i = 0;
    uint32_t len = 0;
    while (ostatok > 0) {
        ostatok = ostatok / 10;
        i++;        
    }
    ostatok = num;
    len = i;
    while (i > 0) {
        buff[i - 1] = ZERO_CHAR + (ostatok % 10);
        ostatok = ostatok / 10;
        i--;
    }
    buff[len] = '\0';
}

uint32_t convert_string_to_int(uint8_t *string) {

}

static inline uint8_t sumbole_down_convert(uint8_t sumb) {
    switch(sumb)
    {
        case 1:   return 'E'; //ESC
        case 14:  return 'B'; // Back space \b
        case 15:  return 'T'; // TAB \t
        case 28:  return 'E'; //ENTER \n
        case 29:  return 'C'; //CTRL
        case 42:  return 'S'; //SHIFT L
        case 54:  return 'S'; //SHIFT R
        case 56:  return 'A'; //ALT
        case 57:  return 'S'; //SPACE
        case 58:  return 'C'; //CAPS LOC
        case 91:  return 'W'; //WIN BUTTON L
        case 92:  return 'W'; //WIN BUTTON R

        case 59:  return '1'; //F1
        case 60:  return '2'; //F2
        case 61:  return '3'; //F3
        case 62:  return '4'; //F4
        case 63:  return '5'; //F5
        case 64:  return '6'; //F6
        case 65:  return '7'; //F7
        case 66:  return '8'; //F8
        case 67:  return '9'; //F9
        case 68:  return 'F'; //F10
        case 87:  return 'F'; //F11
        case 88:  return 'F'; //F12

        case 72:  return '^'; //row up
        case 75:  return '<'; //row left
        case 77:  return '>'; //row right
        case 80:  return 'v'; //row down

        case 2:   return '1';
        case 3:   return '2';
        case 4:   return '3';
        case 5:   return '4';
        case 6:   return '5';
        case 7:   return '6';
        case 8:   return '7';
        case 9:   return '8';
        case 10:  return '9';
        case 11:  return '0';
        
        case 12:  return '-';
        case 13:  return '=';
        case 16:  return 'q'; 
        case 17:  return 'w';
        case 18:  return 'e';
        case 19:  return 'r';
        case 20:  return 't';
        case 21:  return 'y';
        case 22:  return 'u';
        case 23:  return 'i';
        case 24:  return 'o';
        case 25:  return 'p';
        case 26:  return '[';
        case 27:  return ']';
        case 30:  return 'a';
        case 31:  return 's';
        case 32:  return 'd';
        case 33:  return 'f';
        case 34:  return 'g';
        case 35:  return 'h';
        case 36:  return 'j';
        case 37:  return 'k';
        case 38:  return 'l';
        case 39:  return ';';
        case 40:  return '\'';
        case 41:  return '`'; //Ё
        case 43:  return '\\';
        case 44:  return 'z';
        case 45:  return 'x';
        case 46:  return 'c';
        case 47:  return 'v';
        case 48:  return 'b';
        case 49:  return 'n';
        case 50:  return 'm';
        case 51:  return ',';
        case 52:  return '.';
        case 53:  return '/';

        case 55:  return '*'; //NUM PAD * + PRINT SCRIN
        case 69:  return 'P'; //PAUSE
        case 70:  return 'S'; //SCRLK
        case 71:  return 'H'; //HOME
        case 73:  return 'U'; //PAGE UP
        case 79:  return '1'; //NUM PAD + END
        case 81:  return '3'; //NUM PAD + PAGE DOWN
        case 83:  return '.'; //NUM PAD + DEL
        case 74:  return '-'; //NUM PAD
        case 76:  return '5'; //NUM PAD
        case 78:  return '+'; //NUM PAD
        case 82:  return '0'; //NUM PAD

        case 84:  return '1'; 
        case 85:  return '2'; 
        case 86:  return '3'; 
        case 89:  return '3'; 
        case 90:  return '4'; 

        default:  return '\0';
    }
}

static inline uint8_t sumbole_up_convert(uint8_t sumb) {
    switch (sumb) {
    /* --- специальные клавиши (128 + исходный) --- */
        case 129: return 'E';   // ESC
        case 142: return 'B';   // Backspace
        case 143: return 'T';   // Tab
        case 156: return 'E';   // Enter
        case 157: return 'C';   // Ctrl
        case 170: return 'S';   // L-Shift
        case 182: return 'S';   // R-Shift
        case 184: return 'A';   // Alt
        case 185: return 'S';   // Space
        case 186: return 'C';   // CapsLock
        case 219: return 'W';   // L-Win
        case 220: return 'W';   // R-Win
        case 187: return '1';   // F1
        case 188: return '2';   // F2
        case 189: return '3';   // F3
        case 190: return '4';   // F4
        case 191: return '5';   // F5
        case 192: return '6';   // F6
        case 193: return '7';   // F7
        case 194: return '8';   // F8
        case 195: return '9';   // F9
        case 196: return 'F';   // F10
        case 215: return 'F';   // F11
        case 216: return 'F';   // F12

        /* --- стрелки --- */
        case 200: return '^';   // Up
        case 203: return '<';   // Left
        case 205: return '>';   // Right
        case 208: return 'v';   // Down

        /* --- цифровой ряд --- */
        case 130: return '!';   // 1
        case 131: return '@';   // 2
        case 132: return '#';   // 3
        case 133: return '$';   // 4
        case 134: return '%';   // 5
        case 135: return '^';   // 6
        case 136: return '&';   // 7
        case 137: return '*';   // 8
        case 138: return '(';   // 9
        case 139: return ')';   // 0
        case 140: return '_';   // -
        case 141: return '+';   // =

        /* --- буквы верхнего регистра --- */
        case 144: return 'Q';
        case 145: return 'W';
        case 146: return 'E';
        case 147: return 'R';
        case 148: return 'T';
        case 149: return 'Y';
        case 150: return 'U';
        case 151: return 'I';
        case 152: return 'O';
        case 153: return 'P';
        case 154: return '{';
        case 155: return '}';
        case 158: return 'A';
        case 159: return 'S';
        case 160: return 'D';
        case 161: return 'F';
        case 162: return 'G';
        case 163: return 'H';
        case 164: return 'J';
        case 165: return 'K';
        case 166: return 'L';
        case 167: return ':';
        case 168: return '"';
        case 169: return '~';   // Ё
        case 171: return '|';
        case 172: return 'Z';
        case 173: return 'X';
        case 174: return 'C';
        case 175: return 'V';
        case 176: return 'B';
        case 177: return 'N';
        case 178: return 'M';
        case 179: return '<';
        case 180: return '>';
        case 181: return '?';

        /* --- NumPad & прочее --- */
        case 183: return '*';   // Num *
        case 197: return 'P';   // Pause
        case 198: return 'S';   // ScrollLock
        case 199: return 'H';   // Home
        case 201: return 'U';   // PageUp
        case 207: return '1';   // Num End
        case 209: return '3';   // Num PgDn
        case 211: return '.';   // Num Del
        case 202: return '-';   // Num -
        case 204: return '5';   // Num 5
        case 206: return '+';   // Num +
        case 210: return '0';   // Num 0
        case 212: return '1';   // Num 1
        case 213: return '2';   // Num 2
        case 214: return '3';   // Num 3
        case 217: return '3';   // Num 3
        case 218: return '4';   // Num 4

        default:  return '\0';
    }
}