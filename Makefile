
SRC=	$(wildcard src/*.c)

OBJ=	$(SRC:.c=.o)

NAME=	hook-machine

all: $(NAME)

$(NAME): $(OBJ)
	 gcc -o $(NAME) $(OBJ)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re:	fclean all
