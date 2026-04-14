#include "uint.h"
#include "interapts/interapt.h"

uint8_t press_key = 0;

static inline uint8_t sumbole_convert(uint8_t sumb) {
    switch(sumb)
    {
        case 1:   return 'E'; //ESC
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
        case 14:  return 'B'; // Back space \b
        case 15:  return 'T'; // TAB \t
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
        case 28:  return 'E'; //ENTER \n
        case 29:  return 'C'; //CTRL
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
        case 42:  return 'S'; //SHIFT L
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
        case 54:  return 'S'; //SHIFT R
        case 55:  return '*'; //NUM PAD * + PRINT SCRIN
        case 56:  return 'A'; //ALT
        case 57:  return 'S'; //SPACE
        case 58:  return 'C'; //CAPS LOC
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
        case 69:  return 'P'; //PAUSE
        case 70:  return 'S'; //SCRLK
        case 71:  return 'H'; //HOME
        case 72:  return '^'; //row up
        case 73:  return 'U'; //PAGE UP
        case 74:  return '-'; //NUM PAD
        case 75:  return '<'; //row left
        case 76:  return '5'; //NUM PAD
        case 77:  return '>'; //row right
        case 78:  return '+'; //NUM PAD
        case 79:  return '1'; //NUM PAD + END
        case 80:  return 'v'; //row down
        case 81:  return '3'; //NUM PAD + PAGE DOWN
        case 82:  return '0'; //NUM PAD
        case 83:  return '.'; //NUM PAD + DEL
        case 84:  return '1'; 
        case 85:  return '2'; 
        case 86:  return '3'; 
        case 87:  return 'F'; //F11
        case 88:  return 'F'; //F12
        case 89:  return '3'; 
        case 90:  return '4'; 
        case 91:  return 'W'; //WIN BUTTON L
        case 92:  return 'W'; //WIN BUTTON R
        default:   return '\0';
    }
}
void scan_key(void) {
    
    while(press_key == 0) {
        __asm__ __volatile__ ("int $0x21");
        __asm__ __volatile__ ("hlt");
    }
    press_key = sumbole_convert(press_key);
    if (press_key != '\0'){
        uint8_t* vm = (uint8_t*)0xb8000;
        vm[2] = press_key;
    }
    press_key = 0;

}
