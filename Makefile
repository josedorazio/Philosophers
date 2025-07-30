# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2025/07/30 18:45:08 by jdorazio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
#  find *.c | xargs echo

SRCS =  src/main.c src/utils.c src/init.c src/actions.c src/monitor.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinc -pthread
#-g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
