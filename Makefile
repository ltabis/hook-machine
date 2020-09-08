
SRC=	$(wildcard src/*.c) \
	$(wildcard src/utilities/*.c)

OBJ=	$(SRC:.c=.o)

NAME=	hook-machine

CFLAGS= -g -W -Wall -Wextra -iquote include/

all: $(NAME)

$(NAME): $(OBJ)
	 gcc $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
