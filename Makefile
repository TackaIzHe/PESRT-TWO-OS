KERNEL_NAME      := full_kernel.bin
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
CC               := cc
GASM             := as
LINKER           := ld

ASM_BINS         := boot.bin zeroes.bin
ASM_FILES        := kernel_entry.o

KERNEL_CO_FLAG   := --static -nostdlib -ffreestanding -m32 -fno-PIC -fno-stack-protector

KERNEL_ASM_FILES := kernel.o
KERNEL_INT       := keybord.o timer.o null.o
KERNEL_IDT       := pic.o idt.o io.o
KERNEL_GDT       := gdt.o tss.o
KERNEL_FILES     := ${KERNEL_GDT} ${KERNEL_IDT} kernel.o string.o second_kernel.o stdio.o ${KERNEL_INT}

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

%.o: ${OBJ_DIR}/${KERNEL_ASM_DIR}/%.s
	${GASM} --march=i386 --32 --elf-stt-common=yes $^ -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^ -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/interapts/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^  -o ${OBJ_DIR}/$@

%.o: ${SOURCE_DIR}/${KERNEL_DIR}/idt/%.c
	${CC} ${KERNEL_CO_FLAG} -c $^ -o ${OBJ_DIR}/$@

LINK:
	cd ${OBJ_DIR} && \
	${LINKER} -m elf_i386 -T ../link.ld -o ../${BIN_DIR}/${KERNEL_NAME} ${ASM_FILES} ${KERNEL_FILES} --oformat binary
	cd ${BIN_DIR} && \
	cat *.bin > ${OS_NAME}

START_QEMU:
	qemu-system-x86_64 -drive format=raw,file=${BIN_DIR}/${OS_NAME},index=0,if=floppy -m 128M #-d int -d cpu -no-reboot

mkdir:
	@echo -e '\033[0;93m !!! Make directory !!! \033[0m'
	mkdir -p ${BIN_DIR} ${OBJ_DIR} ${OBJ_DIR}/${KERNEL_ASM_DIR}

clean_obj:
	@echo -e '\033[0;93m !!! Clean objects !!! \033[0m'
	rm -r ${OBJ_DIR}

clean:
	@echo -e '\033[0;93m !!! Clean objects and binnaries !!! \033[0m'
	rm -r ${BIN_DIR} ${OBJ_DIR}