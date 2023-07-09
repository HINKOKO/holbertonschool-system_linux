CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
TASK0 = $(wildcard *.c)
TARGET = hobjdump

# always consider out-of-date hnm program
.PHONY: clean hnm

hnm:
	$(CC) $(FLAGS) $(TASK0) -o hnm

hobjdump:
	cd ./my_objdump
	$(CC) $(FLAGS) *.c -o hobjdump

clean:
	rm -rf hnm

