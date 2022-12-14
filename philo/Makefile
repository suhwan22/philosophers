# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suhkim <suhkim@student.4seoul.kr>         +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0/09/30 0:33:0 by suhkim            #+#    #+#                   #
#    Updated: 2022/12/14 13:05:57 by suhkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Werror -Wall -Wextra

SRC = main.c \
	  check_valid_arg.c \
	  utils.c \
	  mutex.c \
	  init.c \
	  thread_philo.c \
	  philo.c \
	  philo_utils.c \
	  thread_monitor.c

OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:all clean fclean re
