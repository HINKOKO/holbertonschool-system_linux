CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic
TASK0 = $(wildcard *.c)

# always consider out-of-date hnm program
.PHONY: clean hnm

hnm:
	$(CC) $(FLAGS) $(TASK0)

clean:
	rm -rf hnm
