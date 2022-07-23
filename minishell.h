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
# include <readline/readline.h>
# include <readline/history.h>
# include "debug.h"
# define WORD 1
# define PIPE 2
// # define SPACE 3
# define PARENTHESIS 4
# define REDIRECTION 5
# define AND 6
# define SEMI 7

// typedef enum{
// 	WORD,
// 	PIPESPACE,
// 	PARENTHESIS,
// 	REDIRECTION,
// 	AND,
// 	SEMI
// }	tokens;

typedef struct s_gen
{
	int	lent;
} t_gen;


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
	int				her_doc_num;
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
	int				lent;
	char			*first_export;
	int				flag_s;
	id_t			flag_d;
	t_env			*lst_env;
	t_cmd			*lst_cmd;
	t_lexer			*lst_lexer;
}	t_data;

//-----------------env--------------------------//
void	ft_create_env_list(t_env **envi, char **env);
void	ft_env(t_data *data);
void	ft_free_env(t_env *env);
void	ft_print_env(t_env	*env, int flag, int fd);

void	free_split(char **arguments);

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
int		ft_change_flag(int flag);
char	*ft_get_value(t_data *data, char *var);
int		ft_check_var_env(t_data *data, char *var);
char	*ft_delete_var(t_data *data, char *var);
int		ft_len_before(char *var);
int		ft_len_after(char *var);
int		ft_len_var(char *var);
int		ft_check_still_dollar(t_data *data);



//----------------parsing----------------------//
void	ft_parsing(t_data *data);
char	*ft_strjoin(char *s1, char *s2);
void	ft_add_command_pipe(t_data *data);
t_cmd	*ft_add_back_cmd(t_data *data, int *fd, int *red, int red_num);
void	ft_add_normal_command(t_data *data);
char	**ft_split(char *s, char c);
char	*ft_join_args(char *s1, char *s2);
void	free_split(char **arguments);
void	ft_free_cmd(t_cmd *cmd);
void	ft_print_cmd(t_cmd *cmd);
char	*ft_substr(char *s, int start, size_t len);

void	ft_delete_quotes(t_data *data);
void	ft_delete_eof_quotes(char *eof);
char	**ft_new_split(char *s, char c);



//-----------------builtinh-------------------------//
int 	echo(t_data *data, t_cmd *cmd_lst, int fd);
int		cd(t_data *data, t_cmd *lst_cmd);
int		pwd(t_data *data, t_cmd *lst_cmd, int fd);
int		unset(t_data *data, t_cmd *lst_cmd);
int		export(t_data *data, t_cmd *lst_cmd, int fd);
void	ft_env_built(t_data *data);
int		ft_change_env_value(t_data *data, char *name, char *value, int	value_size);
void	ft_add_new_env(t_data *data, char *name, char *value);
void	ft_sort_env(t_data *data);
char	*ft_get_value_exp(char *value);
char	*ft_get_name_exp(char *name);
int		ft_name_exists(t_data *data, char *name);

//*-----------------execution----------------------//
int		execution(t_data *data);
int		start_execution(t_data *data, int **pip, int idx, int pid);
void	ft_get_paths(t_data *data);
char	*ft_cmd_exist(t_data *data, t_cmd *lst_cmd, int idx);
int		ft_if_builtin(t_data *data, t_cmd *lst_cmd);
int		**ft_init_pipes(t_data *data, int idx, int old_input, int old_output);
int		ft_execute_cmd(t_data *data, char *path, t_cmd *lst_cmd);
int		ft_dup(int lent, t_cmd *lst_cmd, int **pip);
int		close_pipes(int **pipes, int lent);
int		close_fds(t_cmd *lst_cmd);
int		non_fork_funcs(t_data *data, t_cmd *cmd);
int		init_signals(t_data *data);
//-----------------utils------------------------//
void	ft_putstr_fd(char *s, int fd);
char	*ft_get_env(t_data *data, char *name);

int ft_herdoc(t_data *data);

int		ft_strlen(char *str);

void	ft_add_new_env(t_data *data, char *name, char *value);
t_env	*ft_new_node(char *name, char *value);

#endif
