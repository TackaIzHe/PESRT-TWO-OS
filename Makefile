KERNEL_NAME      := full_kernel.elf
OS_NAME          := PESRT-TWO-OS.bin

QEMU_FLAGS       := -serial stdio -d in_asm,cpu,int,guest_errors,unimp -no-reboot -no-shutdown

SOURCE_DIR       := src
ASM_DIR          := ASM
ASM_DIR_B        := to_binaries
ASM_DIR_O        := to_object
OBJ_DIR          := obj
BIN_DIR          := bin
KERNEL_DIR       := kernel
KERNEL_ASM_DIR   := kernel_asm
ASM_COMPILER     := nasm
CC               := i386-elf-gcc
GASM             := as
LINKER           := i386-elf-ld

ASM_BINS         := boot.bin
ASM_FILES        := kernel_entry.o

KERNEL_CO_FLAG   ?= --static -nostdlib -ffreestanding -m32 -fno-PIC -fno-stack-protector

KERNEL_ASM_FILES := kernel.o
KERNEL_INT       := keybord.o timer.o null.o video.o
KERNEL_IDT       := pic.o idt.o io.o
KERNEL_GDT       := gdt.o tss.o
KERNEL_FILES     := ${KERNEL_GDT} ${KERNEL_IDT} string.o stdio.o ${KERNEL_INT} second_kernel.o kernel.o

.PHONY: all debug ASM KERNEL LINK START_QEMU mkdir clean_obj clean


all:
	@echo -e '\033[0;93m !!! Create dirs \033[0m'
	make mkdir
	@echo -e '\033[0;93m !!! Compile start !!! \033[0m'
	@echo -e '\033[0;93m !!! Compile ASM !!! \033[0m'
	make ASM
	@echo -e '\033[0;93m !!! Compile KERNEL !!! \033[0m'
	make KERNEL
	@echo -e '\033[0;93m !!! Link kernel !!! \033[0m'
	make LINK

debug:
	make all KERNEL_CO_FLAG="${KERNEL_CO_FLAG} -g -O0"

ASM:  ${ASM_BINS} ${ASM_FILES}
	@echo -e '\033[0;93m !!! ASM ready !!! \033[0m'

%.o: ${SOURCE_DIR}/${ASM_DIR}/${ASM_DIR_O}/%.asm
	${ASM_COMPILER} $^ -f elf -o ${OBJ_DIR}/$@

%.bin: ${SOURCE_DIR}/${ASM_DIR}/${ASM_DIR_B}/%.asm
	${ASM_COMPILER} $^ -f bin -o ${BIN_DIR}/$@

KERNEL: ${KERNEL_ASM_FILES} ${KERNEL_FILES}
	@echo -e '\033[0;93m !!! Kernel ready !!! \033[0m'

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/first_kernel/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^ -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^ -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/interapts/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^  -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/idt/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^ -o ${OBJ_DIR}/$@

LINK:
	cd ${OBJ_DIR} && \
	${LINKER} --gc-sections -m elf_i386 -Ttext 0x1000 -o ../${BIN_DIR}/full_kernel.elf ${ASM_FILES} ${KERNEL_FILES} -Map ../bin/map.txt
	cd ${BIN_DIR} && \
	objcopy -O binary --strip-all \
        --only-section=.text \
        --only-section=.rodata \
        --only-section=.data \
        --only-section=.bss \
        ${KERNEL_NAME} full_kernel.bin && \
	cat *.bin > ${OS_NAME}

START_QEMU:
	qemu-system-i386 -drive format=raw,file=${BIN_DIR}/${OS_NAME},index=0,if=floppy -m 128M -no-reboot #-s -S #-d int -d cpu

mkdir:
	@echo -e '\033[0;93m !!! Make directory !!! \033[0m'
	mkdir -p ${BIN_DIR} ${OBJ_DIR} ${OBJ_DIR}/${KERNEL_ASM_DIR}

clean_obj:
	@echo -e '\033[0;93m !!! Clean objects !!! \033[0m'
	rm -r ${OBJ_DIR}

clean:
	@echo -e '\033[0;93m !!! Clean objects and binnaries !!! \033[0m'
	rm -r ${BIN_DIR} ${OBJ_DIR}