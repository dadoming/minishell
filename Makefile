NAME = minishell

INCLUDES = includes/minishell.h \
		includes/variables.h \
		includes/my_lib.h \
		includes/colors.h \

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS = srcs/main.c \
	srcs/get_var_from_envp.c \

MY_LIB = srcs/my_lib/constructor.c \
		srcs/my_lib/string/string_1.c \
		srcs/my_lib/string/string_2.c \
		srcs/my_lib/string/string_3.c \
		srcs/my_lib/string/string_4.c \
		srcs/my_lib/string/string_5.c \
		srcs/my_lib/string/string_6.c \
		srcs/my_lib/string/string_7.c \
		srcs/my_lib/string/string_8.c \
		srcs/my_lib/string/string_9.c \

CC = gcc

FLAGS = -Wextra -Wall -Werror -lreadline

RM = rm -f

all: 
	@echo "Compiling..."
	@${CC} ${FLAGS} ${SRCS} ${MY_LIB} ${GNL} -o ${NAME} -I.${INCLUDES}
