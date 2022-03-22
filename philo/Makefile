NAME = philo

SRC = philo.c \
		error.c \
		checks.c \
		symposium.c \
		utils.c \
		utils_2.c \
		utils_3.c \
		time.c

SRCS = $(addprefix src/, $(SRC))

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
