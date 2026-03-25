#include "kernel.h"

char *videoMem = START_VIDEO_MEM;
// long long int second;
// char keyBuffer[256];

// // long ticks (long delay){
// //     unsigned long long tik = getTackt();
// //     unsigned long long tik1 = getTackt();
// //     while (1){
// //         tik1 = getTackt();
// //         if(tik1 - tik >=delay){
// //             break;
// //         }
// //     }
// //     return  tik1 - tik;
// // }

void printf(char* mess, int color ){
    if(color == 0){
        color = 0x0f;
    }
    int i = 0;
    char *j = videoMem;
    while( mess[i] != 0 )
    {
        *j = mess[i];
        j += 1;
        *j = color;
        j += 1;
        i++;   
    }
}

// void print(int mess){
//     char i[2] = {}; 
//     i[1] = 0;
//     if(mess<10){
//         *i = (char)(ZERO_CHAR + mess);
//         printf(i,0);    
//     }
//     else{ 
//         i[0] = (char)(ZERO_CHAR + (mess % 10));
//         print(mess / 10);
//         printf(i,0);
//     }
// }

// void clearScrin()
// {
//     int *j = videoMem;
//     while(*j != 0xb8000)
//     {
//         *(char*)*j = 0;
//         *j -= 2;
//     }
// }

// char presKey(){
//     return keyboard_interrupt_handler();
// }

void init()
{
    videoMem = START_VIDEO_MEM;
    // second = 999999999999999999;
    // keybord_init();

}


int main(){
    init();

    char qwe[10] = "asd";
    printf(qwe,0);
    return 0;
}
