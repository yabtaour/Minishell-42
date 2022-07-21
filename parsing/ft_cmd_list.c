#include "../minishell.h"

t_cmd	*ft_create_new_command(char *command, int fd_in, int fd_out)
{
	t_cmd	*cmd;
	char	**all_cmd = NULL;
	int		i = 0;

	cmd = malloc(sizeof(t_cmd));
	if (command)
		all_cmd = ft_new_split(command, ' ');
	cmd->her_doc_num = 0;
	while (all_cmd[i])
	{
		if (!strcmp(all_cmd[i], "<<"))
			cmd->her_doc_num++;
		i++;
	}
	cmd->cmd = all_cmd;
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*ft_add_back_cmd(t_data *data, int *fd, int *red, int red_num)
{
	int		fd_in = 0;
	int		fd_out = 1;
	int		i = 0;
	t_lexer	*lexer_clone;
	t_cmd	*node;
	t_cmd	*cmd_clone;
	char	*command = NULL;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		command = ft_strjoin(command, lexer_clone->value);
		command = ft_strjoin(command, " ");
		lexer_clone = lexer_clone->next;
	}
	while (i < red_num)
	{
		if (red[i] == 1 || red[i] == 2)
			fd_out = fd[i];
		else if (red[i] == 3)
			fd_in = fd[i];
		i++;
	}
	node = ft_create_new_command(command, fd_in, fd_out);
	free(command);
	if (!data->lst_cmd)
		return (node);
	cmd_clone = data->lst_cmd;
	while (cmd_clone->next)
		cmd_clone = cmd_clone->next;
	cmd_clone->next = node;
	node->prev = cmd_clone;
	return (data->lst_cmd);
}

void	ft_add_command_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	while (data->lst_lexer)
		ft_add_normal_command(data);
}