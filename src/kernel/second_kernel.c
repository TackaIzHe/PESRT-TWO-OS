#include "first_kernel/kernel.h"
#include "stdio.h"
#include "uint.h"

void main(void)
{
// __asm__ __volatile__ ("int $0x81");
// char* vm = START_VIDEO_MEM;
// *vm = '9';
// uint16_t* vm = (uint16_t*)0xb8000;
// *(vm+4) = 0x01 << 8 |'A';
__asm__ __volatile__ ("sti");
// __asm__ __volatile__ ("int $0x20");
// __asm__ __volatile__ ("int $0x20");
// __asm__ __volatile__ ("int $0x20");
// __asm__ __volatile__ ("int $0x20");
    // // while(1)
    // // {
    //     //     // *(vm + 2) = ':';
    //     //     if (keybord_state == 1)
    //     //     {
    //         //         *(vm + 2) = '2';
    //         //         break;
    //         //     }
    //         //     else{
    //             //         // *(vm + 2) = '6';
    //             //         *(vm + 2) = '8';
    //             //         continue;
    //             //     }
    //             // }
    // while(1){






    ////////////////////////////////////////////////////////////
    /// Какието траблы с прерывание клавиатуры нужно искать инфу
    ////////////////////////////////////////////////////////////
        // __asm__ __volatile__ ("int $0x21");
    //     if (keybord_state == 1)
    //         break;
    // }
    while(1){
        __asm__ __volatile__ ("hlt");
    }

    // __asm__ __volatile__ ("cli");


    // __asm__ __volatile__ ("int $0x80");
    
    return;
}