CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic
SERVER:=ignition.c

SRC4:= $(SERVER) 4-request.c
SRC5:= $(SERVER) 5-queries.c
SRC6:= $(SERVER) 6-headers.c
SRC7:= $(SERVER) 7-body.c


NAME4:=todo_api_0
NAME5:=todo_api_1
NAME6:=todo_api_2
NAME7:=todo_api_3


todo_api_0:
	$(CC) $(FLAGS) $(SRC4) -o $(NAME4)

todo_api_1:
	$(CC) $(FLAGS) $(SRC5) -o $(NAME5)

todo_api_2:
	$(CC) $(FLAGS) $(SRC6) -o $(NAME6)

todo_api_3:
	$(CC) $(FLAGS) $(SRC7) -o $(NAME7)



clean:
	find  -type f -executable -delete
