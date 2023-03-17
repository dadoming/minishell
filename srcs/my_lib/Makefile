# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 13:07:40 by dadoming          #+#    #+#              #
#    Updated: 2023/03/17 13:31:44 by dadoming         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../../.my_lib.a
HEADER = my_lib.h

MY_LIB = constructor.c check/check1.c check/check2.c lst/lst2.c lst/lst1.c string/string_3.c \
		string/string_7.c string/string_2.c string/string_6.c string/string_5.c string/string_4.c \
		string/string_1.c string/string_10.c string/string_9.c string/string_8.c
OBJS = ${MY_LIB:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIB = ar rcs
RM = rm -f

.c.o: 
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I.${HEADER}

${NAME}: ${OBJS} 
	@${LIB} ${NAME} ${OBJS}

all: ${NAME}
	@${RM} *.o

clean: 
	@${RM} ${OBJS}
	@${RM} ${BONUS_OBJS}

fclean: clean
	@${RM} ${NAME} ${BONUS_OBJS}

re: fclean all

.PHONY: all re clean fclean
