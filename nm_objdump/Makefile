CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
TASK0 = $(wildcard *.c)
TASK1 = $(wildcard objdump_*.c)

TARGET = hobjdump

# always consider out-of-date hnm program
.PHONY: clean hnm hobjdump

hnm:
	$(CC) $(FLAGS) $(TASK0) -o hnm

hobjdump:
	$(CC) $(FLAGS) obj_bored_man.c -o hobjdump

clean:
	rm -rf hnm
	rm -rf hobjdump

