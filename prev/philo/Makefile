# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 16:42:07 by anifanto          #+#    #+#              #
#    Updated: 2021/12/16 18:11:02 by anifanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

SRCS = philo.c	philo_utils.c	life_of_philos.c	monitor.c

LIST = $(addprefix src/, $(SRCS))

CFLAGS = -Wall -Wextra -Werror -pthread

compile :
	$(CC) $(CFLAGS) $(LIST) $< -o $(NAME)

all: compile

%.o : %.c
	$(CC) $(CFLAGS) $< -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
