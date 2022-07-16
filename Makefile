NAME = minishell

YBA = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = main.c ft_free.c ft_print_list.c execut.c \
	  ft_delete_quotes.c

ENV = ./env/ft_env.c ./env/ft_env_list.c\

PARSING = ./parsing/parsing.c ./parsing/parsing_utils.c \
		  ./parsing/ft_cmd_list.c\

LEXER = ./lexer/lexer.c ./lexer/lexer_utils.c \
		./lexer/ft_lexer_list.c ./lexer/ft_expanding.c \
		./lexer/ft_add_and.c ./lexer/ft_add_semi.c \
		./lexer/ft_add_parenth.c ./lexer/ft_add_word.c \
		./lexer/ft_add_pipe.c ./lexer/ft_add_redirection.c


SYNTAX = ./syntax/syntax_analyzer.c ./syntax/ft_pipe.c \
	 	 ./syntax/ft_redirection.c ./syntax/ft_quotes.c \

BUILTIN= ./builtin/echo.c ./builtin/cd.c ./builtin/pwd.c ./builtin/export.c ./builtin/unset.c \

UTILS= ./utils/ft_putstr_fd.c ./utils/ft_get_env.c \

FILES = $(SRC) $(PARSING) $(LEXER) $(ENV) $(SYNTAX) $(BUILTIN) $(UTILS)

RSAF = execut.c $(FILES)

OBJ = ${FILES:.c=.o}

RSAF_OBJ = ${RSAF:.c=.o}
 
%.o: %.c minishel.h
	$(CC) $(FLAGS) -c $< -I /Users/yabtaour/.brew/opt/readline/include -o $@

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) $(OBJ) -L/Users/yabtaour/.brew/opt/readline/lib -lreadline -o ${NAME}

env: $(RSAF_OBJ)
	cc $(RSAF_OBJ) -L/Users/yabtaour/.brew/opt/readline/lib -lreadline -o execute

clean_execute:
	rm -rf $(RSAF_OBJ) execute

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ${NAME}

re: fclean all

