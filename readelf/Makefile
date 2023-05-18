CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
FILES_0 = $(wildcard 0-*.c) header_tools.c
FILES_1 = $(wildcard 1-*.c)
HEADER = $(wildcard *.h)

0-hreadelf:
	$(CC) $(FLAGS) $(FILES_0) -o 0-hreadelf

1-hreadelf:
	$(CC) $(FLAGS) $(FILES_1) -o 1-hreadelf
	
clean:
	rm 0-hreadelf 1-hreadelf
