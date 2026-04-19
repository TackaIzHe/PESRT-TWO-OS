#include "../uint.h"
#include "../string.h"
#include "vbe.h"
#include "../stdio.h"
#include "../idt/tss.h"

vbe_info_block_t vbe_info  = {0};
vbe_mode_info_block_t mode_info = {0};
// Выделяем ядерный стек (8 КБ)
static uint8_t g_kernel_stack[8192] __attribute__((aligned(16)));

static inline void load_v86_segments(void) {
    __asm__ __volatile__(
        "mov %0, %%ax\n\t"
        "mov %%ax, %%es\n\t"
        :
        : "r" ((uint16_t)0x07C0)
        : "ax"
    );
}

static inline void vbe_get_controller_info(vbe_info_block_t* info_block) {
    uint32_t addr = (uint32_t)info_block;
    if (addr >= 0x10000) {
        // ОШИБКА: буфер вне реального режима
        while(1); // зависаем
    }
    uint16_t segment = (uint16_t)(addr >> 4);  // ES = addr / 16
    uint16_t offset  = (uint16_t)(addr & 0xF); // DI = addr % 16
    call_interrupt(0x4F00, 0, offset, segment);
}

static inline void vbe_get_mode_info(uint16_t mode_number, vbe_mode_info_block_t* mode_info) {
    uint32_t addr = (uint32_t)mode_info;
    if (addr >= 0x10000) {
        while(1); // зависаем
    }
    uint16_t segment = (uint16_t)(addr >> 4);
    uint16_t offset  = (uint16_t)(addr & 0xF);
    call_interrupt(0x4F01, mode_number, offset, segment);
}

static inline void vbe_set_mode(uint16_t mode_number) {
    call_interrupt(0x4F02, mode_number | 0x4000, 0, 0);
}

void init_graphics_vbe(void) {
    // Буфер в нижних 64KB — обязательно!

    vbe_get_controller_info(&vbe_info);

    // Проверка: VESA-совместимость
    // if (memcmp(vbe_info.signature, "VESA", 4) != 0) {
    //     return; // VBE не поддерживается
    // }
    printf("%s\n", vbe_info.signature);
    printf("VBE Version: %d\n", vbe_info.version);
  printf("Total Memory: %d MB\n", vbe_info.total_memory * 64 / 1024);

    uint16_t desired_mode = 0x11B; // 1024x768x24

    vbe_get_mode_info(desired_mode, &mode_info);

    // Проверка: режим поддерживает графику и доступен
    if (!(mode_info.attributes & (1 << 7))) { // Bit 7: Mode is supported
        goto _exit;
    }

     printf("Framebuffer: 0x%d\n", mode_info.framebuffer);
    printf("Resolution: %dx%d, %dbpp\n", mode_info.width, mode_info.height, mode_info.bits_per_pixel);



    vbe_set_mode(desired_mode);
_exit:
}

void enter_vm86_mode(vm86_regs_t* vm86_context) {
    // Указатель на вершину стека (верхний адрес)
    uint32_t g_kernel_stack_top = (uint32_t)(g_kernel_stack + sizeof(g_kernel_stack));
    
    // 1. Установить IP и CS в VM86-контексте
    //    Предположим: CS = 0x1000, IP = 0x0000 — начало виртуального сегмента
    vm86_context->cs = 0x1000;   // Пример: сегмент кода виртуальной 8086 задачи
    vm86_context->ip = 0x0000;   // Стартовый IP
    vm86_context->ss = 0x1000;   // Сегмент стека
    vm86_context->sp = 0xFFFF;   // Верх стека

    // 2. Установить флаг VM (бит 17) в EFLAGS
    vm86_context->flags = 0x00000200; // VM = 1, IF = 1 (разрешить прерывания)

    // 3. Установить регистры сегментов в соответствии с реальными сегментами
    //    В VM86 mode сегменты используются как в Real Mode: смещение = сегмент * 16
    vm86_context->ds = 0x1000;
    vm86_context->es = 0x1000;
    vm86_context->fs = 0x1000;
    vm86_context->gs = 0x1000;

    // 4. Установить TSS: ESP0 — стек ядра при входе в ядро из VM86 (для обработки прерываний)
    tss.esp0 = (uint32_t)&g_kernel_stack_top; // Убедитесь, что g_kernel_stack_top определён
    tss.ss0 = 0x10; // Дескриптор сегмента ядра (ring 0)

    // 5. Установить EFLAGS и EIP в TSS (не обязательно, но для надёжности)
    tss.eip = (uint32_t)vm86_context->ip;
    tss.eflags = vm86_context->flags;

    // 6. Загрузить TSS в процессор
    asm volatile("ltr %%ax" :: "a" (0x28)); // 0x28 — смещение TSS в GDT (пример)

    // 7. Подготовить стек для IRET — в стеке должен лежать: SS, ESP, EFLAGS, CS, IP
    //    Мы будем использовать "виртуальный" стек задачи, но для перехода — нужно "подделать" IRET
    //    Для этого используем "фальшивый" стек в ядре, который затем будет использован IRET

    // 8. Поместить контекст в стек, как если бы мы делали CALL
    //    Но для перехода в VM86 — мы используем IRET с флагом VM
    //    Поэтому подготовим стек для IRET

    uint32_t* stack_ptr = (uint32_t*)&g_kernel_stack_top;
    *(--stack_ptr) = vm86_context->ss;   // SS
    *(--stack_ptr) = vm86_context->sp;   // ESP
    *(--stack_ptr) = vm86_context->flags | 0x200; // EFLAGS (VM=1)
    *(--stack_ptr) = vm86_context->cs;   // CS
    *(--stack_ptr) = vm86_context->ip;   // IP

    // 9. Установить указатель стека на этот стек
    asm volatile(
        "mov %0, %%esp\n"      // Установить ESP на подготовленный стек
        "iret\n"               // IRET переключит в VM86 mode!
        :
        : "r" (stack_ptr)
        : "memory"
    );
    // После IRET — процессор перейдёт в VM86 mode и начнёт выполнять код по CS:IP
    // Эта функция НЕ возвращается!
}
