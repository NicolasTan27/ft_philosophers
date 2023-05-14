# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 14:33:36 by ntan              #+#    #+#              #
#    Updated: 2022/05/07 16:17:19 by ntan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	srcs/main.c \
					srcs/memory.c \
					srcs/utils.c \
					srcs/print_time.c \
					srcs/check_end.c \
					srcs/philo_create.c \
					srcs/philo_life.c \
					srcs/init_prog.c

OBJS			= 	$(SRCS:.c=.o)

CC				= 	gcc
RM				= 	rm -f
CFLAGS			= 	-Wall -Wextra -Werror -g
NAME			= 	philo

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -pthread -I. $(SRCS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			
				$(RM) $(OBJS)
				$(RM) $(NAME)

re:				fclean all