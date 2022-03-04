# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 16:42:07 by anifanto          #+#    #+#              #
#    Updated: 2021/12/17 10:39:06 by anifanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

SRCS = philo_bonus.c	philo_utils_bonus.c	life_of_philos_bonus.c	check_meal_bonus.c

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

bonus: all

re: fclean all

.PHONY: all clean fclean re
