CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
C_FILES = $(wildcard *.c)
HEADER = $(wildcard *.h)

0-hreadelf:
	$(CC) $(FLAGS) $(C_FILES) -o 0-hreadelf

1-hreadelf:
	$(CC) $(FLAGS) 1-hreadelf.c -o 1-hreadelf
	
clean:
	rm 0-hreadelf
