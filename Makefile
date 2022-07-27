NAME = minishell

YBA = minishell

CC = gcc

CPPFLAGS	= -I /goinfre/rsaf/.brew/opt/readline/include
LDFLAGS   	= -L /goinfre/rsaf/.brew/opt/readline/lib


INCLUDESS        =  ${CPPFLAGS}

LIBRARIESS        = ${LDFLAGS} -lreadline

FLAGS = -Wall -Wextra -Werror

SRC = main.c ft_free.c \

ENV = ./env/ft_env.c ./env/ft_env_list.c\

PARSING = ./parsing/parsing.c ./parsing/parsing_utils.c \
		  ./parsing/ft_cmd_list.c ./parsing/ft_new_split.c \
		  ./delete_quotes/ft_delete_quotes.c ./delete_quotes/delete_quotes_utils.c \
		  ./parsing/exit_status.c ./parsing/parsing_utils2.c ./parsing/parsing_utils3.c\
		  ./parsing/parsing_utils4.c ./parsing/parsing_utils5.c \

EXPANDING = ./expanding/ft_expanding.c ./expanding/expanding_utils.c \
			./expanding/ft_len.c ./expanding/expanding_utils2.c \

LEXER = ./lexer/lexer.c ./lexer/lexer_utils.c \
		./lexer/ft_lexer_list.c \
		./lexer/ft_add_and.c ./lexer/ft_add_semi.c \
		./lexer/ft_add_parenth.c ./lexer/ft_add_word.c \
		./lexer/ft_add_pipe.c ./lexer/ft_add_redirection.c


SYNTAX = ./syntax/syntax_analyzer.c ./syntax/ft_pipe.c \
	 	 ./syntax/ft_redirection.c ./syntax/ft_quotes.c \

BUILTIN= ./builtin/echo.c ./builtin/cd.c ./builtin/pwd.c ./builtin/unset.c \
		 ./builtin/env.c ./builtin/export/export.c ./builtin/export/export_utils.c \
		 ./builtin/export/export_utils2.c ./builtin/export/export_utils3.c \
		 ./builtin/exit.c \

UTILS= ./utils/ft_putstr_fd.c ./utils/ft_get_env.c ./utils/ft_itoa.c \
	   ./utils/ft_strcmp.c ./utils/ft_strlen.c ./utils/ft_calloc.c \
	   ./utils/ft_strchr.c ./utils/ft_trim.c \

EXECUT= ./execution/execution.c ./execution/ft_get_path.c ./execution/ft_cmd_exist.c \
		./execution/ft_if_builtin.c ./execution/ft_init_pipes.c\
		./execution/start_execution.c ./execution/ft_dup.c ./execution/close_fds.c \
		./execution/non_fork_funcs.c ./execution/herdoc.c init_signals.c\

FILES = $(SRC) $(PARSING) $(LEXER) $(ENV) $(SYNTAX) $(BUILTIN) $(UTILS) $(EXPANDING) $(EXECUT)

OBJ = ${FILES:.c=.o}
 
%.o: %.c minishel.h
	$(CC) $(FLAGS) -c $< ${INCLUDESS} -o $@

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) ${LIBRARIESS} $(OBJ) -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ${NAME}

re: fclean all

