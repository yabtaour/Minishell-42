#include "../minishell.h"

void	ft_handle_herdoc(t_data *data)
{
	t_lexer	*lexer;
	int		i;

	i = 0;
	lexer = data->lst_lexer;
	while (lexer)
	{
		if (ft_strcmp(lexer->value, "<<") == 0)
			data->her_doc++;
		lexer = lexer->next;
	}
	data->eof = malloc(sizeof(char *) * data->her_doc + 1);
	lexer = data->lst_lexer;
	while (lexer)
	{
		if (ft_strcmp(lexer->value, "<<") == 0)
		{
			lexer = lexer->next;
			data->eof[i] = ft_substr(lexer->value, 0, ft_strlen(lexer->value));
			ft_delete_eof_quotes(data->eof[i]);
			i++;
		}
		lexer = lexer->next;
	}
	data->eof[i] = NULL;
}

void	ft_delete_command(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->next)
			lexer_clone->next->prev = lexer_clone->prev;
		if (lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		data->lst_lexer = lexer_clone->next;
		free(lexer_clone);
		lexer_clone = data->lst_lexer;
	}
	if (lexer_clone)
	{
		if (lexer_clone->next)
			lexer_clone->next->prev = lexer_clone->prev;
		if (lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		data->lst_lexer = lexer_clone->next;
		free(lexer_clone);
		lexer_clone = data->lst_lexer;
	}
}

char	**ft_get_new(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**new_cmd;
	int		len;

	i = 1;
	new_cmd = NULL;
	while (cmd->cmd && cmd->cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * i - (cmd->her_doc_num * 2) + 1);
	if (!new_cmd)
		return (NULL);
	len = 0;
	i = -1;
	while (cmd->cmd && cmd->cmd[++i])
	{
		if (!ft_strcmp(cmd->cmd[i], "<<"))
			i += 1;
		else
		{
			new_cmd[len] = ft_substr(cmd->cmd[i], 0, ft_strlen(cmd->cmd[i]));
			len++;
		}
		new_cmd[len] = NULL;
	}
	return (new_cmd);
}

void	ft_delete_herdoc(t_data *data)
{
	t_cmd	*cmd_clone;
	char	**new_cmd;
	int		len;
	int		i;

	cmd_clone = data->lst_cmd;
	while (cmd_clone->next)
		cmd_clone = cmd_clone->next;
	if (cmd_clone && cmd_clone->her_doc_num)
	{
		new_cmd = ft_get_new(data, cmd_clone);
		free_split(cmd_clone->cmd);
		i = 0;
		while (new_cmd && new_cmd[i])
			i++;
		cmd_clone->cmd = malloc (sizeof(char *) * i + 1);
		i = 0;
		while (new_cmd && new_cmd[i])
		{
			cmd_clone->cmd[i] = ft_substr(new_cmd[i], 0, ft_strlen(new_cmd[i]));
			i++;
		}
		cmd_clone->cmd[i] = NULL;
		free_split(new_cmd);
	}		
}
