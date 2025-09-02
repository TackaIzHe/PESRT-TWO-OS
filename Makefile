all:
	nasm src/start.asm -f bin -o bin/start.bin
	nasm src/print.asm -f bin -o bin/print.bin
	
	gcc src/main.c -m32 -o bin/main.bin
	# ld -o bin/main.bin bin/main.o 
	 
	cat bin/start.bin bin/print.bin bin/main.bin > bin/start.img

	qemu-system-x86_64 -drive format=raw,file="bin/start.img",index=0,if=floppy,  -m 128M