CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic
SRC_0 := $(wildcard 0*.c)
SRC_1 := $(wildcard 1*.c)
SRC_2 := $(wildcard 2*.c)

EXEC_0 := strace_0
EXEC_1 := strace_1
EXEC_2 := strace_2

strace_0:
	$(CC) $(FLAGS) $(SRC_0) -o $(EXEC_0)

strace_1:
	$(CC) $(FLAGS) $(SRC_1) -o $(EXEC_1)

strace_2:
	$(CC) $(FLAGS) $(SRC_2) -o $(EXEC_2)

clean:
	find -type f -executable -delete
