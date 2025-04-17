export PATH=$PATH:/home/tackaizhe/Desktop/build/gcc-i686-elf/bin
export PATH=$PATH:/home/tackaizhe/Desktop/build/binutils-i686-elf/bin
export PATH=$PATH:/home/tackaizhe/Desktop/build/gcc-i686-elf/gcc

nasm "boot.asm" -f bin -o "Binaries/boot.bin"
nasm "kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"
nasm "keybord.asm" -f elf -o "Binaries/keybord.o"

cc1 "kernel.c" -ffreestanding -m32 -o "Binaries/kernel.s"
as --32 --elf-stt-common=yes "Binaries/kernel.s" -o "Binaries/kernel.o"


nasm "zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i686-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/keybord.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin"  > "Binaries/OS.bin"

qemu-system-x86_64 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy,  -m 128M
