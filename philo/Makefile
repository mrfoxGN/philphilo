NAME = philo

SRC = \
    src/main.c \
    src/philo.c \
    src/philo_utils.c \
    src/philotime.c \
    src/norme.c \
    src_libft/strings.c \
    src_libft/numbers.c \
    src_libft/lists.c 


OBJ = $(SRC:.c=.o)
INC = -Iincludes
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf src/*.o src_libft/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJ)

.PHONY: all clean fclean re
