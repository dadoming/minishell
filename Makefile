NAME = minishell

INCLUDES = includes/minishell.h \
		includes/variables.h

LIBFT = libft/libft.a

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS = srcs/main.c \
	srcs/get_var_from_envp.c \

CC = gcc

FLAGS = -Wextra -Wall -Werror

RM = rm -f

all: ${LIBFT}
	@echo "Compiling..."
	@${CC} ${FLAGS} ${SRCS} ${GNL} ${LIBFT} -o ${NAME} -I.${INCLUDES}

${LIBFT}:
	cd libft/ && make clean
	cd libft/ && make bonus