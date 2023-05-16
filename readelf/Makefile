CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
FILES_0 = 0-hreadelf.c general_print_elf.c print_elf32_1.c print_elf32_2.c print_elf64_1.c print_elf64_2.c print_utils.c swapper.c
FILES_1 = $(wildcard 1-*.c)
HEADER = $(wildcard *.h)

0-hreadelf:
	$(CC) $(FLAGS) $(FILES_0) -o 0-hreadelf

1-hreadelf:
	$(CC) $(FLAGS) $(FILES_1) -o 1-hreadelf
	
clean:
	rm 0-hreadelf 1-hreadelf
