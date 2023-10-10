CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic
SERVER:=ignition.c

SRC4:= $(SERVER) 4-request.c
SRC5:= $(SERVER) 5-queries.c
SRC6:= $(SERVER) 6-headers.c


NAME4:=todo_api_0
NAME5:=todo_api_1
NAME6:=todo_api_2


todo_api_0:
	$(CC) $(FLAGS) $(SRC4) -o $(NAME4)

todo_api_1:
	$(CC) $(FLAGS) $(SRC5) -o $(NAME5)

todo_api_2:
	$(CC) $(FLAGS) $(SRC6) -o $(NAME6)



clean:
	find  -type f -executable -delete
