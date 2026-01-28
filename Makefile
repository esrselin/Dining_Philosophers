NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g 

SRCS = main.c parse.c utils.c daily.c time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re