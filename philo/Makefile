NAME = philo
SRCS = philo.c philo_make.c philo_sitting.c philo_print.c philo_ending.c philo_utils.c
OBJS = $(SRCS:.c=.o)
INCS = philo.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

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
