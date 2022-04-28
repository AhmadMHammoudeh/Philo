# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 08:21:23 by ahhammou          #+#    #+#              #
#    Updated: 2022/04/28 14:59:52 by ahhammou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g -pthread

SOURCES = actions.c helpers.c inting.c philosophers.c protein.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(OBJECTS)
	gcc $(CFLAGS) $(SOURCES) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJECTS)
	rm -rf *.dSYM

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re  
