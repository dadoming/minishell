NAME = minishell

INCLUDES = includes/minishell.h \
		includes/variables.h \
		includes/my_lib.h \
		includes/colors.h \

SRCS = ${wildcard srcs/*.c} \
		${wildcard srcs/built_in/*.c} \
		${wildcard srcs/my_lib/*.c} \
		${wildcard srcs/my_lib/string/*.c} \
		${wildcard srcs/my_lib/check/*.c} \
		${wildcard srcs/my_lib/lst/*.c} \

CC = gcc

FLAGS = -Wextra -Wall -Werror

RM = rm -f

all: 
	@echo "Compiling..."
	@${CC} ${FLAGS} -L.local/lib ${SRCS} -o ${NAME} -lreadline -I.${INCLUDES}
