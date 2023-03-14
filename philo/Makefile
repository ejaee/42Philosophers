# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 20:28:44 by choiejae          #+#    #+#              #
#    Updated: 2023/03/14 19:17:26 by ejachoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME 		=	philo

SRCS		=	main.c \
				philo.c \
				init.c \
				utils.c \
				error.c \
				property.c \
				
OBJS		= $(SRCS:%.c=%.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o			:	%.c
		$(CC) $(CFLAGS) -c $^ -I./ -o $@

clean		:
		$(RM) $(OBJS)
		
fclean		:	clean
		$(RM) $(NAME)
		
re			:
		$(MAKE) fclean
		$(MAKE) all

.PHONY		:	all clean fclean re bonus
