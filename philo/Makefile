NAME = philo
SRCS = philo.c make_philo.c start_eating.c print_state.c
OBJS = $(SRCS:.c=.o)
INCS = philo.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all : $(NAME)

$(NAME) : $(OBJS) $(INCS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $(SRCS)
clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re