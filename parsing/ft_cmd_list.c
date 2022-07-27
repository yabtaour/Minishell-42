/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:01 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 21:30:37 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initialize(t_cmd *cmd, char *command, int fd_in, int fd_out)
{
	char	**all_cmd;

	all_cmd = NULL;
	if (command)
		all_cmd = ft_new_split(command, ' ');
	cmd->cmd = all_cmd;
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	cmd->next = NULL;
	cmd->prev = NULL;
}

t_cmd	*ft_create_new_command(char *command, int fd_in, int fd_out)
{
	t_cmd	*cmd;
	int		i;
	int		pip[2];

	pipe(pip);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit (1);
	ft_initialize(cmd, command, fd_in, fd_out);
	cmd->her_doc_num = 0;
	cmd->her_in = 1;
	i = 0;
	while (cmd->cmd && cmd->cmd[i])
	{
		if (!ft_strcmp(cmd->cmd[i], "<<"))
		{
			fd_in = pip[0];
			cmd->her_in = pip[1];
			cmd->her_doc_num++;
		}
		i++;
	}
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	return (cmd);
}

char	*ft_fill_command(t_data *data)
{
	char	*command;
	t_lexer	*lexer_clone;

	command = NULL;
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		command = ft_strjoin(command, lexer_clone->value);
		command = ft_strjoin(command, " ");
		lexer_clone = lexer_clone->next;
	}
	return (command);
}

t_cmd	*ft_add_back_cmd(t_data *data, int *fd, int *red, int red_num)
{
	int		fd_in;
	int		fd_out;
	t_cmd	*node;
	t_cmd	*cmd_clone;
	char	*command;

	ft_delete_redirections(data);
	command = ft_fill_command(data);
	fd_in = ft_get_in(fd, red, red_num);
	fd_out = ft_get_out(fd, red, red_num);
	free(fd);
	free(red);
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
	char	*new;

	while (data->lst_lexer)
	{
		new = NULL;
		ft_add_normal_command(data, new);
		ft_delete_herdoc(data);
		ft_delete_command(data);
	}
}
