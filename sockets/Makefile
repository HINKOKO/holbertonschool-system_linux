CC=gcc
FLAGS=-Wall -Werror -Wextra -pedantic -g
SERVER:=ignition.c
API_SERVER:=server_api.c

SRC4:= $(SERVER) 4-request.c
SRC5:= $(SERVER) 5-queries.c
SRC6:= $(SERVER) 6-headers.c
SRC7:= $(SERVER) 7-body.c
SRC8:= $(SERVER) 8-create_todo.c util_functions.c
SRC9:= $(SERVER) 9-pick_em_all.c util_functions.c

# SRC8ALT:= $(API_SERVER) 8-to_refactor.c util_functions.c api_response.c


NAME4:=todo_api_0
NAME5:=todo_api_1
NAME6:=todo_api_2
NAME7:=todo_api_3
NAME8:=todo_api_4
NAME9:=todo_api_5


todo_api_0:
	$(CC) $(FLAGS) $(SRC4) -o $(NAME4)

todo_api_1:
	$(CC) $(FLAGS) $(SRC5) -o $(NAME5)

todo_api_2:
	$(CC) $(FLAGS) $(SRC6) -o $(NAME6)

todo_api_3:
	$(CC) $(FLAGS) $(SRC7) -o $(NAME7)

todo_api_4:
	$(CC) $(FLAGS) $(SRC8) -o $(NAME8)

todo_work:
	$(CC) $(FLAGS) $(SRC8ALT) -o todo_work

todo_api_5:
	$(CC) $(FLAGS) $(SRC9) -o $(NAME9)


clean:
	find  -type f -executable -delete
