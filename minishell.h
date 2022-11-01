/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:37:28 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/07 13:04:44 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# define WORD 1
# define PIPE 2
# define PARENTHESIS 4
# define REDIRECTION 5
# define AND 6
# define SEMI 7
# define TERM_OWNER 130
# define NO_BUILT 4242
# define HEREDOC_EXE 42424242

typedef struct s_gvar
{
	int	g_where_ami;
	int	g_exit_stat;
	int	g_heredoc;
	int	g_continue_exe;
	int	g_pid;
}	t_gvar;

t_gvar	g_vars;

typedef struct s_gen
{
	int				index;
	int				count;
	int				old_error;
}					t_gen;

typedef struct s_split
{
	int				i;
	int				j;
	int				d;
	int				s;
	char			**ptr;
}					t_split;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_lexer
{
	char			*val;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	int				her_doc_num;
	int				idx;
	int				her_in;
	int				fd_out;
	int				fd_in;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_uwu
{
	char	*lexer;
	char	*new;
	char	*temp;
	int		i;
	int		j;
}		t_uwu;

typedef struct s_data
{
	int				exit_stat;
	int				fork_flag;
	int				rerror_f;
	int				ac;
	char			*cmd;
	char			**av;
	char			**env;
	char			**paths;
	char			**eof;
	int				her_doc;
	t_gen			general;
	char			cwd[256];
	char			*first_export;
	int				flag_s;
	int				flag_d;
	int				**pipes;
	t_env			*lst_env;
	t_cmd			*lst_cmd;
	t_lexer			*lst_lexer;
}					t_data;

//--------------------execution soukaina--------------------//
int					ft_statushandling(int status);
int					ft_builtins(t_data *data);
int					my_exit(t_cmd *lst_cmd, int old_error);
int					my_pwd(t_data *data, t_cmd *lst_cmd);
int					my_cd(t_data *data, t_cmd *lst_cmd);
int					my_env(t_data *data, t_cmd *lst_cmd);
int					my_echo(t_cmd *lst_cmd);
t_data				*my_export(t_data *data, t_cmd *lst_cmd);
int					execution_2(t_data *data, t_cmd *cmd);
int					check_access(t_data *data, char **cmd, int i, int flag);
void				update_env(t_data *data, char *env, char *upd);
char				*custom_getenv(char *env_var, t_env *env_lst);
int					**initialize_pipes(t_data *data);
int					my_strchr(char *s, int c);
char				*ft_strcat(char *dest, char *src);
char				*ft_strdup(char *src);
int					count_cmds(char **cmd);
long				ft_atoi(const char *str);
int					c_lstcmd(t_data *data);
int					pre_execution(t_data *data);
void				fork_func(t_data *data);
int					close_all(t_cmd *lst_cmd, int **pipes, int count);
void				sig_handler(int num);
int					heredoc_exec(t_data *data, t_cmd *cmd_lst, int idx);
int					nofork_list(t_data *data, t_cmd *cmd);
int					check_nonfork(t_data *data, t_cmd *cmd);
int					check_fork(int *pid, t_data *data);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*custom_getenv(char *env_var, t_env *env_lst);
char				*join_cmd(char **argv, int argc, int i);
int					check_valid(char *cmd);
int					check_builtins(t_data *data, t_cmd *cmd_lst);
char				*cd_strjoin(char *s1, char *s2);
t_data				*update_pwd(t_data *data, char *cwd);
int					valid_name(char *name, t_data **data);
int					check_delim_idx(t_data *data, t_cmd *cmd);
int					close_pipes(int **pip, int lent);
int					close_fds(t_cmd *lst_cmd);
int					go_back_minus(t_data *data);
void				print_error(void);
int					go_home(t_data *data, char *cwd);
int					ft_check_name(t_data *data, char *name, char *value);
int					terminate_pid(pid_t lastchild);
int					check_delim_idx(t_data *data, t_cmd *cmd);
void				print_her_in(t_cmd *cmd, char *here_buff);
void				init_sig(void);
void				init_main(t_data *data);
void				ft_initialize2(t_data *data);
int					check_path(t_env *lst_env);
//-----------------env--------------------------//
void				ft_create_env_list(t_env **envi, char **env);
void				ft_env(t_data *data);
void				ft_free_env(t_env *env);
void				ft_print_env(t_env *env, int flag, int fd);
t_env				*ft_add_to_env_back(t_env *envi, char *value);
void				free_split(char **arguments);
void				ft_create_my_env(t_data *data);
t_env				*ft_new_env_node(char *value);
//-----------------Lexer------------------------//
void				ft_lexer(t_data *data);
t_lexer				*ft_add_lexer_back(t_lexer *lexer, char *str, int type);
void				ft_free_lexer(t_lexer *lexer);
void				ft_print_lexer(t_lexer *lexer);
int					ft_add_pipe(t_data *data, int i);
int					ft_add_word(t_data *data, int i);
int					ft_add_redirection(t_data *data, int i);
int					ft_add_parenth(t_data *data, int i);
int					ft_add_and(t_data *data, int i);
int					ft_add_semi(t_data *data, int i);
int					ft_is_word(char c);
int					ft_is_parenth(char c);
int					ft_is_redirection(char c);
int					ft_isspace(char c);
//------------Syntax analyzer-----------------//
int					ft_syntax_analyzer(t_data *data);
int					ft_check_redirection(t_data *data);
int					ft_check_between_pipes(t_data *data);
int					ft_check_quotes(t_data *data);
//-------------Expanding------------------------//
void				ft_expanding(t_data *data);
int					ft_skip(char *value, int i);
int					ft_change_flag(int flag);
char				*ft_get_value(t_data *data, char *var);
int					ft_check_var_env(t_data *data, char *var);
char				*ft_delete_var(t_data *data, char *var);
int					ft_len_before(char *var);
int					ft_len_after(char *var);
int					ft_len_var(char *var);
char				*ft_var_isnt(t_data *data, char *lexer, char *n_v);
int					ft_value_var(int i, char *value);
int					ft_check_still_dollar(t_data *data);
char				*ft_fix_norme(char *n_v, char *value, int i);
char				*ft_change_nd_free(char *var, char *n_v);
char				*ft_get_expand_value(char *n_v, int i, char *lexer);
//----------------parsing----------------------//
void				ft_parsing(t_data *data);
char				*ft_strjoin(char *s1, char *s2);
void				ft_add_command_pipe(t_data *data);
t_cmd				*ft_add_back_cmd(t_data *data, int *fd, int *red,
						int red_num);
void				ft_add_normal_command(t_data *data, char *new, int *fd,
						int *red);
char				**ft_split(char *s, char c);
char				*ft_join_args(char *s1, char *s2);
void				free_split(char **arguments);
void				ft_free_cmd(t_cmd *cmd);
void				ft_print_cmd(t_cmd *cmd);
char				*ft_substr(char *s, int start, size_t len);
int					ft_exist_quotes(char *cmd);
char				*ft_delete(char *cmd);
void				ft_delete_quotes(t_data *data);
void				ft_delete_eof_quotes(char *eof);
char				**ft_new_split(char *s, char c);
int					*ft_get_index(char *cmd, int type);
int					ft_real_len(char *cmd);
void				ft_change_exit_status(t_data *data);
int					ft_get_in(int *fd, int *red, int red_num);
int					ft_get_out(int *fd, int *red, int red_num);
void				ft_delete_command(t_data *data);
void				ft_handle_herdoc(t_data *data, t_lexer *lexer, int i);
void				ft_delete_herdoc(t_data *data);
int					*ft_fill_red(t_data *data, int red_num);
int					ft_fill_fd(t_data *data, char *name, int red);
int					ft_red_num(t_data *data);
void				ft_delete_redirections(t_data *data);
int					ft_check_still_redirection(t_data *data);
char				*ft_new(char *old);
//-----------------builtins-------------------------//
int					unset(t_data *data, t_cmd *lst_cmd);
int					export(t_data *data, t_cmd *lst_cmd);
int					ft_env_built(t_data *data, int fd);
int					ft_change_env_value(t_data *data, char *name, char *value);
void				ft_add_new_env(t_data *data, char *name, char *value);
void				ft_sort_env(t_data *data);
char				*ft_get_value_exp(char *value);
char				*ft_get_name_exp(char *name);
int					ft_name_exists(t_data *data, char *name);
void				ft_concatenate(t_data *data, char *name, char *value);
int					ft_check_concate(char *name);
//-----------------utils------------------------//
void				ft_putstr_fd(char *s, int fd);
char				*ft_get_env(t_data *data, char *name);
int					ft_herdoc(t_data *data, t_cmd *cmd_lst, int **pip, int i);
void				ft_print_cmd1(t_cmd *cmd);
void				ft_add_new_env(t_data *data, char *name, char *value);
t_env				*ft_new_node(char *name, char *value);
char				*ft_itoa(int n);
void				handler(int sig);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_calloc(int count, int size);
char				**ft_free_tab(char **str, int i);
char				*ft_strchr(char *s, int c);
char				*ft_strtrim(char *s1, char *set);
int					ft_sub_main(t_data *data);
void				ft_free_norme(t_data *data);

#endif
