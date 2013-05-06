all: elf.c
	gcc -Wall -Wextra -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings  -Wl,-z,relro,-T./linker.ld  -g elf.c -o elf

full: elf.c
	gcc -Wall -Wextra -Wl,-z,relro,-z,now -g elf.c -o elf

run: all
	LD_BIND_NOW=1 ./elf
