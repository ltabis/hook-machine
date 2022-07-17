
SRC = src/hook_machine.c 	\
	src/plugin.c 			\
	src/utilities/map.c

TEST = tests/main.c

SRC_OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST:.c=.o)

NAME = hm
LIB_NAME = lib$(NAME).a
TEST_NAME = test-$(NAME)

CFLAGS = -g -W -Wall -Wextra -iquote include/

all : $(NAME)

$(NAME) : $(SRC_OBJ)
	ar rc $(LIB_NAME) $(SRC_OBJ)

test : $(NAME) $(TEST_OBJ)
	gcc -o $(TEST_NAME) $(TEST_OBJ) -L. -l$(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)

fclean : clean
	rm -f $(TEST_NAME)
	rm -f $(LIB_NAME)

re : fclean all
