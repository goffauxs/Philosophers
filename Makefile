# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 12:00:15 by sgoffaux          #+#    #+#              #
#    Updated: 2021/09/10 10:40:32 by sgoffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc
INCLUDE	=	includes
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
RM		=	rm -f

SRCS	=	philosophers.c \
			srcs/utils.c \
			srcs/atoitoa.c \
			srcs/init.c \
			srcs/philo_functions.c \
			srcs/threads.c

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "Linked into executable \033[0;32mphilo\033[0m."

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			@echo "Compiling $<."

clean:
			@$(RM) $(OBJS)
			@echo "Removed object files."
			
fclean:		clean
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean all

.PHONY:		all clean fclean re
