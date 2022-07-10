#include "minishell.h"

void	ft_print_2d(char **str, char *type)
{
	int	i = 0;

	printf("%s =", type);
	if (str)
	{
		while (str[i])
		{
			printf(" %s ", str[i]);
			i++;
		}
	}
}

void	ft_print_lexer(t_lexer *lexer)
{
	t_lexer	*lexer_clone;

	lexer_clone = lexer;
	while (lexer_clone)
	{
		printf("[%s - %d]->", lexer_clone->value, lexer_clone->type);
		lexer_clone = lexer_clone->next;
	}
	printf("\n");
}

void	ft_print_env(t_env *env, int flag, int fd)
{
	t_env	*env_clone;

	env_clone = env;
	if (flag == 0)
	{
		while(env_clone)
		{
			printf("%s=%s\n", env_clone->name, env_clone->value);
			env_clone = env_clone->next;
		}
	}
	if (flag == 1)
	{
		while (env_clone)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env_clone->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env_clone->value, fd);
			ft_putstr_fd("\n", fd);
			env_clone = env_clone->next;
		}
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*cmd_clone;

	cmd_clone = cmd;
	while (cmd_clone)
	{
		if (cmd_clone->cmd)
			ft_print_2d(cmd_clone->cmd, "command");
		printf("fd_in %d", cmd_clone->fd_in);
		printf(" fd_out %d\n", cmd_clone->fd_out);
		cmd_clone = cmd_clone->next;
	}
}