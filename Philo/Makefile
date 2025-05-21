CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c philo_routine.c init_philo.c utils.c utils_print.c 

OBJE = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)


$(NAME):$(OBJE)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGC) -c $< -o $@

clean:
	@rm -f $(OBJE)

fclean:clean
	@rm -f $(NAME)

re:fclean all

.PHONY: clean