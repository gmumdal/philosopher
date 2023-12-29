NAME = philo_bonus
SRCS = ph_bonus.c ph_make_bonus.c ph_print_bonus.c ph_utils_bonus.c ph_sema_bonus.c
OBJS = $(SRCS:.c=.o)
INCS = ph_bonus.h
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
