/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:48 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:22:49 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute_cmd(t_data *data, char *path, t_cmd *lst_cmd)
{
	if (lst_cmd->fd_in != 0)
		close(lst_cmd->fd_in);
	if (lst_cmd->fd_out != 1)
		close(lst_cmd->fd_out);
	execve(path, lst_cmd->cmd, data->env);
	return (0);
}

int	cmds_lent(t_data *data)
{
	int		lent;
	t_cmd	*cmd_clone;

	lent = 0;
	cmd_clone = data->lst_cmd;
	while (cmd_clone)
	{
		lent++;
		cmd_clone = cmd_clone->next;
	}
	return (lent);
}

//  this main only for testing.
int	execution(t_data *data)
{
	int	idx;
	int	**pip;
	int	lent;
	int	pid;

	idx = 0;
	pid = 0;
	data->general.pid = -42;
	data->general.lent = cmds_lent(data);
	pip = ft_init_pipes(data, 0, 0, 0);
	ft_get_paths(data);
	if (data->lst_cmd)
		start_execution(data, pip, 0);
	return (0);
}
