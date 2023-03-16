NAME = minishell

INCLUDES = includes/minishell.h \
		includes/my_lib.h \
		includes/colors.h \
		includes/g_var.h \

SRCS = srcs/signals.c srcs/evaluate.c srcs/env_utils.c srcs/prompt.c srcs/helper_print.c srcs/init.c srcs/print_error.c srcs/clear_looped_values.c \
		srcs/main.c srcs/close_program.c srcs/executor.c srcs/my_lib/constructor.c srcs/my_lib/check/check1.c srcs/my_lib/check/check2.c \
		srcs/my_lib/lst/lst2.c srcs/my_lib/lst/lst1.c srcs/my_lib/string/string_3.c srcs/my_lib/string/string_7.c \
		srcs/my_lib/string/string_2.c srcs/my_lib/string/string_6.c srcs/my_lib/string/string_5.c srcs/my_lib/string/string_4.c \
		srcs/my_lib/string/string_1.c srcs/my_lib/string/string_10.c srcs/my_lib/string/string_9.c srcs/my_lib/string/string_8.c \
		srcs/executor/execute_command.c srcs/executor/heredoc.c srcs/executor/parse_pipes.c srcs/executor/reset_fds.c srcs/executor/exec_utils.c \
		srcs/executor/parse_infile.c srcs/executor/parse_outfile.c srcs/executor/is_built_in.c srcs/executor/built_in/echo.c srcs/executor/built_in/pwd.c \
		srcs/executor/built_in/cd.c srcs/executor/built_in/cd_utils.c srcs/executor/built_in/exit.c \
		srcs/executor/built_in/unset.c srcs/executor/built_in/env.c srcs/executor/built_in/export.c srcs/lexer/build_ast_reds.c \
		srcs/lexer/build_ast.c srcs/lexer/utils.c srcs/lexer/expand_replace.c srcs/lexer/lexer.c srcs/lexer/redir_sep.c srcs/lexer/expander.c \
		srcs/lexer/define_type.c srcs/lexer/check_quote.c srcs/lexer/expand_env.c srcs/lexer/has_redir.c srcs/lexer/quotes.c srcs/lexer/expand_utils.c \
		srcs/lexer/expand_replace_utils.c srcs/lexer/quotes_utils.c

CC = gcc

FLAGS = -Wextra -Wall -Werror

RM = rm -f

all: 
	@echo "Compiling..."
	@${CC} ${FLAGS} -L.local/lib -g ${SRCS} -o ${NAME} -lreadline -I.${INCLUDES}

# This makes the program and directly runs it
m:
	make all && ./minishell

v:
	make all && valgrind ./minishell
