# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 13:01:51 by dadoming          #+#    #+#              #
#    Updated: 2023/03/17 18:53:26 by dadoming         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES = includes/minishell.h \
		includes/colors.h \
		includes/g_var.h

SRCS = srcs/signals.c srcs/evaluate.c srcs/env_utils.c srcs/prompt.c srcs/helper_print.c srcs/init.c srcs/print_error.c srcs/clear_looped_values.c \
		srcs/main.c srcs/close_program.c srcs/executor.c srcs/executor/execute_command.c srcs/executor/heredoc.c srcs/executor/parse_pipes.c \
		srcs/executor/wait_child.c srcs/executor/exec_utils.c srcs/executor/parse_infile.c srcs/executor/parse_outfile.c srcs/executor/is_built_in.c \
		srcs/executor/built_in/echo.c srcs/executor/built_in/pwd.c srcs/executor/built_in/cd.c srcs/executor/built_in/cd_utils.c srcs/executor/built_in/exit.c \
		srcs/executor/built_in/unset.c srcs/executor/built_in/env.c srcs/executor/built_in/export.c srcs/lexer/build_ast_reds.c srcs/lexer/build_ast.c \
		srcs/lexer/utils.c srcs/lexer/expand_replace.c srcs/lexer/lexer.c srcs/lexer/redir_sep.c srcs/lexer/expander.c srcs/lexer/define_type.c \
		srcs/lexer/check_quote.c srcs/lexer/expand_env.c srcs/lexer/has_redir.c srcs/lexer/quotes.c srcs/lexer/expand_utils.c srcs/lexer/expand_replace_utils.c \
		srcs/lexer/quotes_utils.c srcs/lexer/remove_non_existent.c
OBJS = $(SRCS:%.c=%.o)

CC = gcc

FLAGS = -Wextra -Wall -Werror

RM = rm -f

MY_LIB = .my_lib.a

all: ${MY_LIB} ${NAME}	

${NAME}: ${MY_LIB} ${OBJS}
	@${CC} ${FLAGS} -L.local/lib -g ${OBJS} ${MY_LIB} -o ${NAME} -lreadline -I.${INCLUDES}

${MY_LIB}:
	@cd srcs/my_lib && make all
	@cd srcs/my_lib && make clean

clean:

fclean:
	${RM} ${NAME}
	${RM} ${MY_LIB}
	${RM} ${OBJS}
	

re: fclean all

m:
	make all && ./minishell

v:
	make all && valgrind ./minishell

.PHONY: all clean fclean re m v
