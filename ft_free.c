#include "minishell.h"

void	ft_free_env(t_env *env)
{
	t_env	*env_current;
	t_env	*env_next;

	env_current = env;
	while (env_current)
	{
		env_next = env_current->next;
		free(env_current->name);
		free(env_current->value);
		free(env_current);
		env_current = env_next;
	}
}

void	ft_free_lexer(t_lexer *lexer)
{
	t_lexer	*lexer_current;
	t_lexer	*lexer_next;

	lexer_current = lexer;
	while (lexer_current)
	{
		lexer_next = lexer_current->next;
		free(lexer_current->value);
		free(lexer_current);
		lexer_current = lexer_next;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*cmd_current;
	t_cmd	*cmd_next;

	cmd_current = cmd;
	while (cmd_current)
	{
		cmd_next = cmd_current->next;
		if (cmd_current->cmd)
			free_split(cmd_current->cmd);
		free(cmd_current);
		cmd_current = cmd_next;
	}
}