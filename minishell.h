#ifndef MINISHEL_H
# define MINISHEL_H

// remark :
// strcmp is forbidden delete when we finish

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "debug.h"
# include <readline/readline.h>
# include <readline/history.h>
# define WORD 1
# define PIPE 2
# define SPACE 3
# define PARENTHESIS 4
# define REDIRECTION 5
# define AND 6
# define SEMI 7


typedef struct s_fds
{
	int	fd_out;
	int	fd_inp;
}	t_fds;


typedef struct s_env{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_lexer{
	char			*value;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_cmd{
	char			**cmd;
	int				fd_out;
	int				fd_in;
	int				*ptr_in;
	int				*ptr_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data{
	int				error;
	int				ac;
	char			*cmd;
	char			**av;
	char			**env;
	char			**paths;
	char			**eof;
	int				her_doc;
	int				ex_code;
	char			*first_export;
	t_env			*lst_env;
	t_cmd			*lst_cmd;
	t_lexer			*lst_lexer;
}	t_data;

//-----------------env--------------------------//
void	ft_create_env_list(t_env **envi, char **env);
void	ft_env(t_data *data);
void	ft_free_env(t_env *env);
void	ft_print_env(t_env	*env, int flag, int fd);

//-----------------Lexer------------------------//
void	ft_lexer(t_data *data);
t_lexer	*ft_add_lexer_back(t_lexer *lexer, char *str, int type);
void	ft_free_lexer(t_lexer *lexer);
void	ft_print_lexer(t_lexer	*lexer);
int		ft_add_pipe(t_data *data, int i);
int		ft_add_word(t_data *data, int i);
int		ft_add_redirection(t_data *data, int i);
int		ft_add_parenth(t_data *data, int i);
int		ft_add_and(t_data *data, int i);
int		ft_add_semi(t_data *data, int i);

int	ft_change_flag(int flag);

int		ft_is_word(char c);
int		ft_is_parenth(char c);
int		ft_is_redirection(char c);

//------------Syntax analyzer-----------------//
int	ft_syntax_analyzer(t_data *data);
int	ft_check_redirection(t_data *data);
int	ft_check_between_pipes(t_data *data);
int	ft_check_quotes(t_data *data);

//-------------Expanding------------------------//
void	ft_expanding(t_data *data);

//----------------parsing----------------------//
void	ft_parsing(t_data *data);
char	*ft_strjoin(char *s1, char *s2);
void	ft_add_command_pipe(t_data *data);
t_cmd	*ft_add_cmd_back(t_cmd *lst_cmd, char *command);
char	**ft_split(char *s, char c);
char	*ft_join_args(char *s1, char *s2);
void	free_split(char **arguments);
void	ft_free_cmd(t_cmd *cmd);
void	ft_print_cmd(t_cmd *cmd);
char	*ft_substr(char *s, int start, size_t len);

void	ft_delete_quotes(t_data *data);


//-----------------exe-------------------------//
int		exe(t_data *data);
int 	echo(t_data *data, t_cmd *cmd_lst, int fd);
int		cd(t_data *data, t_cmd *lst_cmd);
int		pwd(t_data *data, t_cmd *lst_cmd, int fd);
int		unset(t_data *data, t_cmd *lst_cmd);
int		export(t_data *data, t_cmd *lst_cmd, int fd);


//-----------------utils------------------------//
void	ft_putstr_fd(char *s, int fd);
char	*ft_get_env(t_data *data, char *name);

#endif
