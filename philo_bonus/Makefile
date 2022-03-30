NAME = philo_bonus

SRC = philo_bonus.c \
		checks.c \
		error.c \
		print_error.c \
		time.c \
		get.c \
		symposium.c \
		utils.c \
		single_process.c

SRCS = $(addprefix src/, $(SRC))

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
